#pragma once
#include <queue>
#include <string>
#include <functional>

namespace types
{
class FileInfo;
}

namespace common{
using Filter = std::function<bool(const std::string&)>;

class FileBrowser
{
public:
    FileBrowser(const std::string&);
    std::queue<types::FileInfo> extractFiles(const Filter filter = [](const std::string&){return true;});
private:
    const std::string dir;
};
}
