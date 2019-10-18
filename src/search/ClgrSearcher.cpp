#include "ClgrSearcher.hpp"
#include "FileSearcher.hpp"
#include "TextSearcher.hpp"
#include "../common/MatchedLine.hpp"
#include "../common/functions.hpp"
#include "../threads/Pool.hpp"
#include "../output/Result.hpp"
#include <sstream>
#include <iostream>

namespace search {

ClgrSearcher::ClgrSearcher(output::Result& resHandler) : resHandler{resHandler} {}

void ClgrSearcher::setIgnoreCase(bool ic) {
    this->isIgnoreCase = ic;
}

void ClgrSearcher::setMatchWholeWord(bool mww) {
    this->isMatchWholeWord = mww;
}

void ClgrSearcher::setIgnoreFolderName(bool ifn) {
    this->isIgnoreFolderName = ifn;
}

void ClgrSearcher::setUseRegular(bool ur) {
    this->isUseRegular = ur;
}

void ClgrSearcher::search(const std::vector<std::string>& dirs, const std::vector<std::string>& fileKeywords, const std::vector<std::string>& textKeywords) {
    if (textKeywords.size() > 0) {
        searchTexts(dirs, fileKeywords, textKeywords);
    } else {
        searchFiles(dirs, fileKeywords);
    }
    resHandler.SearchConclusion();
}

void ClgrSearcher::searchTexts(const std::vector<std::string>& dirs, const std::vector<std::string>& fileKeywords, const std::vector<std::string>& textKeywords) {
    FileSearcher searcher(dirs);
    searcher.setIgnoreCase(true);
    searcher.setIgnoreFolderName(true);
    searcher.setMatchWholeWord(false);
    searcher.setUseRegular(false);
    std::function<void(const std::string& filename)> textSearchTask = std::bind([](const std::string& filename, const std::vector<std::string>& textKeywords, bool ignoreCase, bool matchWholeWord, bool useRegular) {
        TextSearcher searcher(filename);
        searcher.setIgnoreCase(ignoreCase);
        searcher.setMatchWholeWord(matchWholeWord);
        searcher.setUseRegular(useRegular);
        searcher.setHandlerWhenFindAResult([](const std::string& file, const std::vector<common::MatchedLine>& lines) {
            
        });
        searcher.search(textKeywords);
    }, std::placeholders::_1, textKeywords, isIgnoreCase, isMatchWholeWord, isUseRegular);
    threads::Pool pool(textSearchTask);
    searcher.setHandlerWhenFindAResult([&pool](const std::string& filename) {
        if (common::isTextFile(filename)) {
            pool.addFile(filename);
        }
    });
    pool.start();
    searcher.search(fileKeywords);
    pool.destroy();
}

void ClgrSearcher::searchFiles(const std::vector<std::string>& dirs, const std::vector<std::string>& fileKeywords) {
    FileSearcher searcher(dirs);
    searcher.setIgnoreCase(isIgnoreCase);
    searcher.setIgnoreFolderName(isIgnoreFolderName);
    searcher.setMatchWholeWord(isMatchWholeWord);
    searcher.setUseRegular(isUseRegular);
    searcher.setHandlerWhenFindAResult([](const std::string& file) {
        std::cout << file << std::endl;
    });
    searcher.search(fileKeywords);
}
}