#include "ClgrSearcher.hpp"
#include "FileSearcher.hpp"
#include "TextSearcher.hpp"
#include "../common/MatchedLine.hpp"
#include "../common/functions.hpp"
#include "../threads/Pool.hpp"
#include "../output/Result.hpp"

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
    if (!textKeywords.empty()) {
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
    std::function<void(const std::string& filename)> textSearchTask = std::bind([](const std::string& filename, const std::vector<std::string>& textKeywords, const Flags& flags, output::Result& resHandler) {
        TextSearcher searcher(filename);
        searcher.setIgnoreCase(flags.ignoreCase);
        searcher.setMatchWholeWord(flags.matchWholeWord);
        searcher.setUseRegular(flags.useRegular);
        searcher.setHandlerWhenFindAResult([&resHandler](const std::string& file, const std::vector<common::MatchedLine>& lines) {
            resHandler.GetATextSearchResult(file, lines);
        });
        searcher.search(textKeywords);
    }, std::placeholders::_1, textKeywords, Flags{isIgnoreCase, isMatchWholeWord, true, isUseRegular}, std::ref(resHandler));
    threads::Pool pool(textSearchTask);
    searcher.setHandlerWhenFindAResult([&pool](const std::string& filename) {
        if (common::isTextFile(filename)) {
            pool.addFile(filename);
        }
    });
    pool.start();
    searcher.search(fileKeywords);
    while (pool.hasTasks());
    pool.destroy();
}

void ClgrSearcher::searchFiles(const std::vector<std::string>& dirs, const std::vector<std::string>& fileKeywords) {
    FileSearcher searcher(dirs);
    searcher.setIgnoreCase(isIgnoreCase);
    searcher.setIgnoreFolderName(isIgnoreFolderName);
    searcher.setMatchWholeWord(isMatchWholeWord);
    searcher.setUseRegular(isUseRegular);
    searcher.setHandlerWhenFindAResult([this](const std::string& file) {
        (this->resHandler).GetAFileSearchResult(file);
    });
    searcher.search(fileKeywords);
}
}