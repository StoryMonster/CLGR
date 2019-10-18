#pragma once
#include <string>
#include <vector>
#include <functional>

namespace common {

struct FileInfo {
    ::std::string path;
    ::std::string name;
    bool isDir;
};

void toLower(::std::string&);
::std::vector<FileInfo> listAll(const ::std::string& dir);
bool matchDirectly(const ::std::string& line, const ::std::vector<::std::string>& keywords);
bool matchWholeWord(const ::std::string& line, const ::std::vector<::std::string>& keywords);
bool matchRegular(const ::std::string& line, const ::std::vector<::std::string>& keywords);
std::function<bool(const std::string&)> getMatchFunc(const ::std::vector<::std::string>& keywords, bool ignoreCase, bool matchWholeWord, bool useRegular);

bool isDir(const std::string& path);
bool isTextFile(const std::string& filename);
}