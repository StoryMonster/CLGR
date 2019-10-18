#pragma once
#include <string>
#include <vector>
#include <functional>

namespace search {

class FileSearcher {
public:
    FileSearcher(const std::vector<std::string>& dirs);

    void setIgnoreCase(bool);
    void setMatchWholeWord(bool);
    void setIgnoreFolderName(bool);
    void setUseRegular(bool);
    void setHandlerWhenFindAResult(const std::function<void(const std::string&)>& handler);
    void search(const std::vector<std::string>& keywords);

private:
    bool isIgnoreCase = false;
    bool isMatchWholeWord = false;
    bool isIgnoreFolderName = false;
    bool isUseRegular = false;
    std::function<void(const std::string&)> resultHandler{};
    std::vector<std::string> destDirs{};
};

}