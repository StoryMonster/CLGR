#include "functions.hpp"
#include <algorithm>
#include <cstring>
#include <regex>

#ifdef __WINDOWS__
#include <io.h>
#else
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#endif


namespace common {

const std::string SEPARATE_CHARACTORS = " -+_\\/><*&^%$#!@~`?[]{}()=|:;,.";

void toLower(std::string& str) {
    std::transform(str.begin(), str.end(), str.begin(), [](auto& ch) {
        return (ch >= 'A' && ch <= 'Z') ? ch - 'A' + 'a' : ch;
    });
}

#ifdef __WINDOWS__
std::vector<FileInfo> listAll(const std::string& dir) {
    struct _finddata_t fileInfo;
    long hFile = _findfirst((dir + "/*").c_str(), &fileInfo);
    if (hFile == -1) { return {}; }
    std::vector<FileInfo> files{};
    do {
        if (fileInfo.attrib & _A_SUBDIR) {
            if (strcmp(fileInfo.name, ".") !=0 && strcmp(fileInfo.name, "..") != 0) {
                files.push_back({dir+"\\"+fileInfo.name, fileInfo.name, true});
            }
        }
        else {
            files.push_back({dir+"\\"+fileInfo.name, fileInfo.name, false});
        }
    }while (_findnext(hFile, &fileInfo) == 0);
    _findclose(hFile);
    return files;
}
#else
std::vector<FileInfo> listAll(const std::string& dir) {
    std::vector<FileInfo> files{};
    DIR* pFolder = opendir(dir.c_str());
    if (pFolder == NULL) { return {}; }
    while (true) {
        struct dirent* file = readdir(pFolder);
        if (file == NULL) { break; }
        if (strcmp(file->d_name, "..") == 0 || strcmp(file->d_name, ".") == 0) { continue; }
        if (file->d_type == DT_DIR) {
            files.push_back(FileInfo{dir + "/" + file->d_name, std::string(file->d_name), true});
        } else if (file->d_type == DT_REG) {
            files.push_back(FileInfo{dir + "/" + file->d_name, std::string(file->d_name), false});
        }
    }
    closedir(pFolder);
    return files;
}
#endif

bool matchRegular(const ::std::string& line, const std::vector<std::string>& keywords) {
    if (keywords.empty()) { return false; }
    for (const auto& keyword : keywords) {
        if (std::regex_match(line, std::regex(keyword))) {
            return true;
        }
    }
    return false;
}

bool matchWholeWord(const ::std::string& line, const ::std::vector<::std::string>& keywords) {
    if (keywords.empty()) { return true; }
    for (const auto& keyword : keywords) {
        std::string templine = line;
        while (true) {
            size_t index = templine.find_first_of(keyword);
            if (index == ::std::string::npos) { break; }
            if ((index > 0 && SEPARATE_CHARACTORS.find(templine[index-1]) == std::string::npos) ||
                (index < templine.size()-1 && SEPARATE_CHARACTORS.find(templine[index+1+keyword.size()]) == std::string::npos)) {
                templine = templine.substr(index+1);
                continue;
            }
            return true;
        }
    }
    return false;
}

bool matchDirectly(const ::std::string& line, const ::std::vector<::std::string>& keywords) {
    if (keywords.empty()) { return true; }
    for (const auto& keyword : keywords) {
        if (line.find(keyword) != ::std::string::npos) {
            return true;
        }
    }
    return false;
}

std::function<bool(const std::string&)> getMatchFunc(const ::std::vector<::std::string>& keywords, bool ignoreCase, bool matchWholeWord, bool useRegular) {
    std::vector<::std::string> tempKeywords = keywords;
    if (useRegular) {
        return std::bind(matchRegular, std::placeholders::_1, tempKeywords);
    }
    if (ignoreCase) {
        for (std::string& keyword : tempKeywords) { toLower(keyword); }
    }
    if (matchWholeWord) {
        return std::bind(common::matchWholeWord, std::placeholders::_1, tempKeywords);
    }
    return std::bind(matchDirectly, std::placeholders::_1, tempKeywords);
}

bool isDir(const std::string& path) {
    return true;
}

bool isTextFile(const std::string& filename) {
    std::string binFileSuffixs[] = {
	    // libs
	    ".dll", ".so", ".a",
	    // binary files
	    ".exe", ".out", ".bin", ".apk", ".msi",
	    // microsoft office
	    ".doc", ".pptx", ".ppt", ".xlsm", ".pdf", ".xlsx", ".docx",
	    // video
	    ".mp4", ".avi", ".rmvb",
	    // audio
	    ".mp3", ".wmv",
	    // compress
	    ".tar", ".zip", ".rar",
	    // others
	    ".o", ".pyc"};
    int index = filename.find_last_of(".");
    if (index == std::string::npos) { return true; }
    std::string suffix = filename.substr(index);
    for (const auto& binFileSuffix : binFileSuffixs) {
        if (binFileSuffix == suffix) {
            return false;
        }
    }
    return true;
}
}