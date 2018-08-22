#pragma once
#include <functional>

namespace types
{
struct SearchOptions;
}

namespace common
{
using CaseSensitiveFilter = std::function<bool(const std::string&, const std::string&)>;
using WholeMatchFilter = std::function<bool(const std::string&, const std::string&)>;

class SearchFilterFactory
{
public:
    SearchFilterFactory(const types::SearchOptions&);
    CaseSensitiveFilter createCaseSensitiveFilter();
    WholeMatchFilter createWholeMatchFilter();
    static bool isBasicMatched(const std::string&, const std::string&);

private:
    types::SearchOptions options;
};
}