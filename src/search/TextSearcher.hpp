#pragma once
#include <vector>
#include <string>
#include <functional>

namespace common {
struct MatchedLine;
}

namespace search {

using TextSearchResultHandlerType = std::function<void(const std::string& filename, const std::vector<common::MatchedLine>& lines)>;

class TextSearcher {
public:
    TextSearcher(const std::string& filename);
    void search(const std::vector<std::string>& keywords);
    void setIgnoreCase(bool);
    void setMatchWholeWord(bool);
    void setUseRegular(bool);
    void setHandlerWhenFindAResult(const TextSearchResultHandlerType& handler);

private:
    bool isIgnoreCase = false;
    bool isMatchWholeWord = false;
    bool isUseRegular = false;
    std::string destFile{};
    TextSearchResultHandlerType resultHandler{};
};
}