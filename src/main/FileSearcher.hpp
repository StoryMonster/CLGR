#pragma once
#include "src/common/FileBrowser.hpp"
#include "src/types/SearchInfo.hpp"
#include "src/types/FileInfo.hpp"

class FileSearcher
{
public:
    FileSearcher(const types::SearchField& field)
    : field(field), fileBrowser(field.dir)
    {}

    void search()
    {
        auto searchFilter = [&](const std::string& fileName) {
            if (field.files.size() == 0) {return true;}
            for (const auto& item : field.files)
            {
                if (fileName.size() >= item.size() && fileName.find(item) != std::string::npos)
                {
                    return true;
                }
            }
            return false;
        };
        fileBrowser.showFiles(searchFilter);
    }

private:
    types::SearchField field;
    common::FileBrowser fileBrowser;
};
