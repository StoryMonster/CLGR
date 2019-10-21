#pragma once
#include <vector>
#include <string>

namespace output {
class Result;
}

namespace search {

struct Flags {
    bool ignoreCase = false;
    bool matchWholeWord = false;
    bool ignoreFolderName = false;
    bool useRegular = false;
};

class ClgrSearcher {
public:
    ClgrSearcher(output::Result& resHandler);
    void search(const std::vector<std::string>& dirs, const std::vector<std::string>& fileKeywords, const std::vector<std::string>& textKeywords);
    void setIgnoreCase(bool);
    void setMatchWholeWord(bool);
    void setIgnoreFolderName(bool);
    void setUseRegular(bool);

private:
    void searchTexts(const std::vector<std::string>& dirs, const std::vector<std::string>& fileKeywords, const std::vector<std::string>& textKeywords);
    void searchFiles(const std::vector<std::string>& dirs, const std::vector<std::string>& fileKeywords);

    bool isIgnoreCase = false;
    bool isMatchWholeWord = false;
    bool isIgnoreFolderName = false;
    bool isUseRegular = false;
    output::Result& resHandler;
};

}