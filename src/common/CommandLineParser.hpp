#pragma once
#include <vector>
#include <string>
#include <cstdint>

namespace types
{
struct SearchOptions;
struct SearchInfo;
}

namespace common{

class CommandLineParser
{
public:
    CommandLineParser(int, char**);
    types::SearchInfo parse();

private:
    types::SearchInfo createSearchInfo(const std::string&, const std::vector<std::string>&,
                                       const std::string&, const types::SearchOptions&);
    types::SearchOptions getSearchOptions(const std::string&);
private:
    std::vector<std::string> params;
};
}
