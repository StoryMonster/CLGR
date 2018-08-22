#pragma once
#include "src/common/FileBrowser.hpp"
#include "src/types/SearchInfo.hpp"
#include "src/types/FileInfo.hpp"
#include "src/common/utils.hpp"
#include "src/common/SearchFilterFactory.hpp"
#include <memory>

class FileSearcher
{
public:
    FileSearcher(const types::SearchField& field, const types::SearchOptions& options)
    : field(field)
    , options(options)
    , fileBrowser(field.dir)
    , searchFilterFactory(options)
    , caseSensitiveFilter{searchFilterFactory.createCaseSensitiveFilter()}
    , wholeMatchFilter{searchFilterFactory.createWholeMatchFilter()}
    {
    }

    void search()
    {
        auto searchFilter = [&](const std::string& fileName) {
            if (field.files.size() == 0) { return true; }
            for (const auto& item : field.files)
            {
                if (not common::SearchFilterFactory::isBasicMatched(item, fileName)) { continue; }
                if (wholeMatchFilter(item, fileName) && caseSensitiveFilter(item, fileName))
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
    common::SearchFilterFactory searchFilterFactory;
    common::CaseSensitiveFilter caseSensitiveFilter;
    common::WholeMatchFilter wholeMatchFilter;
};
