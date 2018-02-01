#pragma once
#include "common/Logger.hpp"
#include "common/FileBrowser.hpp"
#include "types/SearchInfo.hpp"
#include "types/FileInfo.hpp"

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
        auto files = fileBrowser.extractFiles(searchFilter);
        while (files.size())
        {
            LOG_INFO << files.front() << "\n";
            files.pop();
        }
    }

private:
    types::SearchField field;
    common::FileBrowser fileBrowser;
};
