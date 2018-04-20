#pragma once
#include "src/common/FileBrowser.hpp"
#include "src/types/SearchInfo.hpp"
#include "src/types/FileInfo.hpp"
#include "src/common/utils.hpp"

class FileSearcher
{
public:
    FileSearcher(const types::SearchField& field, const types::SearchOptions& options)
    : field(field), options(options), fileBrowser(field.dir)
    {}

    void search()
    {
        auto searchFilter = [&](const std::string& fileName) {
            if (field.files.size() == 0) {return true;}
            const auto _fileName = options.caseSensitive ? fileName : common::utils::toLower(fileName);
            for (const auto& item : field.files)
            {
                const auto _item = options.caseSensitive ? item : common::utils::toLower(item);
                if (options.matchWholeWord ? common::utils::isWordWholeMatched(_item, _fileName) :
                                             (_fileName.find(_item) != std::string::npos))
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
    types::SearchOptions options;
    common::FileBrowser fileBrowser;
};
