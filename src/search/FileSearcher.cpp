#include "FileSearcher.hpp"
#include "../common/functions.hpp"
#include <queue>
#include <functional>

#ifdef __WINDOWS__
#include <io.h>
#endif

namespace search {

FileSearcher::FileSearcher(const std::vector<std::string>& dirs) : destDirs{dirs}{}

void FileSearcher::setIgnoreCase(bool ic) {
    this->isIgnoreCase = ic;
}

void FileSearcher::setMatchWholeWord(bool mww) {
    this->isMatchWholeWord = mww;
}

void FileSearcher::setIgnoreFolderName(bool ifn) {
    this->isIgnoreFolderName = ifn;
}

void FileSearcher::setUseRegular(bool ur) {
    this->isUseRegular = ur;
}

void FileSearcher::setHandlerWhenFindAResult(const std::function<void(const std::string&)>& handler) {
    this->resultHandler = handler;
}

void FileSearcher::search(const std::vector<std::string>& keywords) {
    if (destDirs.empty()) { return; }
    std::function<bool(const std::string&)> matchFunc = common::getMatchFunc(keywords, isIgnoreCase, isMatchWholeWord, isUseRegular);
    std::queue<std::string> folders{};
    for (const auto& dir: destDirs) {
        if (common::isDir(dir)) {
            folders.push(dir);
        }
    }

    while (!folders.empty()) {
        std::string folder = folders.front();
        folders.pop();
        std::vector<common::FileInfo> files = common::listAll(folder);
        for (const auto& file : files) {
            if (file.isDir) {
                folders.push(file.path);
                if (isIgnoreFolderName) { continue; }
            }
            std::string temp = file.name;
            if (!isUseRegular && isIgnoreCase) { common::toLower(temp); }
            if (matchFunc(temp)) {
                resultHandler(file.path);
            }
        }
    }
}

}