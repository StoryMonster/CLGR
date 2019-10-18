#include "TextSearcher.hpp"
#include <fstream>
#include "../common/functions.hpp"
#include "../common/MatchedLine.hpp"

namespace search {

TextSearcher::TextSearcher(const std::string& filename): destFile{filename} {}

void TextSearcher::setIgnoreCase(bool ic) {
    this->isIgnoreCase = ic;
}

void TextSearcher::setMatchWholeWord(bool mww) {
    this->isMatchWholeWord = mww;
}

void TextSearcher::setUseRegular(bool ur) {
    this->isUseRegular = ur;
}

void TextSearcher::setHandlerWhenFindAResult(const TextSearchResultHandlerType& handler) {
    this->resultHandler = handler;
}

void TextSearcher::search(const std::vector<std::string>& keywords) try {
    std::function<bool(const std::string&)> matchFunc = common::getMatchFunc(keywords, isIgnoreCase, isMatchWholeWord, isUseRegular);
    std::ifstream in(destFile, std::ifstream::in);
    std::vector<common::MatchedLine> matchedLines{};
    int lineCounter = 0;
    while (in.good()) {
        char buffer[1024] = {0};
        in.getline(buffer, sizeof(buffer));
        std::string line(buffer);
        for (size_t i = 0; i < line.size(); ++i) {
            if (buffer[i] <= 0x08) { return ; }
        }
        if (line.size() < sizeof(buffer)-1) { ++lineCounter; }
        std::string temp = line;
        if (!isUseRegular && isIgnoreCase) { common::toLower(temp); }
        if (matchFunc(temp)) {
            matchedLines.push_back(common::MatchedLine{lineCounter, line});
        }
    }
    in.close();
    if (matchedLines.size() > 0) {
        resultHandler(destFile, matchedLines);
    }
} catch(...) {
    return ;
}

}