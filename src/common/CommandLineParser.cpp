#include "CommandLineParser.hpp"
#include "src/types/SearchInfo.hpp"
#include "src/exceptions/ParserError.hpp"
#include <cstring>

#ifdef __WINDOWS__
#include <direct.h>
#else
#include <unistd.h>
#endif

namespace common{

CommandLineParser::CommandLineParser(int argc, char **argv)
{
    for (auto i = 1; i < argc; ++i)
    {
        params.emplace_back(std::string(argv[i]));
    }
}

types::SearchInfo CommandLineParser::parse()
{
    std::string text, dir;
    std::vector<std::string> files;
    types::SearchOptions options;
    for (const auto& item : params)
    {
        if (item.find("--help") == 0 && item.size() == std::string("--help").size())
        {
            return types::SearchInfo{types::SearchType::help, "", types::SearchField()};
        }
        else if (item.find("--version") == 0 && item.size() == std::string("--version").size())
        {
            return types::SearchInfo{types::SearchType::version, "", types::SearchField()};
        }
        else if (item.find("-f=") == 0)
        {
            files.push_back(item.substr(3));
        }
        else if (item.find("-t=") == 0)
        {
            text = item.substr(3);
        }
        else if (item.find("-d=") == 0)
        {
            dir = item.substr(3);
        }
        else if (item.find("-o=") == 0)
        {
            options = getSearchOptions(item);
        }
        else
        {
            throw exceptions::ParserError("Unknow options! Use --help option to learn how to use");
        }
    }
    return createSearchInfo(text, files, dir, options);
}

types::SearchOptions CommandLineParser::getSearchOptions(const std::string& str)
{
    types::SearchOptions options;
    const auto opts = str.substr(strlen("-o="));
    for (const auto opt : opts)
    {
        switch (opt)
        {
            case 'c': options.caseSensitive = true; break;
            case 'm': options.matchWholeWord = true; break;
            default: break;
        }
    }
    return options;
}

types::SearchInfo CommandLineParser::createSearchInfo(const std::string& text, const std::vector<std::string>& files,
                                                      const std::string& dir, const types::SearchOptions& options)
{
    types::SearchInfo info;
    info.type = (text.size() > 0) ? types::SearchType::text : types::SearchType::file;
    info.text = (info.type == types::SearchType::text) ? text : "";
    info.field.dir = (dir.size() > 0) ? dir : getcwd(NULL, 0);
    info.field.files.resize(files.size());
    std::copy(files.cbegin(), files.cend(), info.field.files.begin());
    info.options = options;
    return info;
}
}
