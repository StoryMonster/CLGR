#include "src/types/SearchInfo.hpp"
#include "SearchFilterFactory.hpp"
#include "src/common/utils.hpp"

namespace common
{
SearchFilterFactory::SearchFilterFactory(const types::SearchOptions& options) : options{options}
{
}

WholeMatchFilter SearchFilterFactory::createWholeMatchFilter()
{
    if (options.matchWholeWord)
    {
        return [](const std::string& text, const std::string& dest) {
            return utils::isWordWholeMatched(text, dest);
        };
    }
    // no matter whether the word is whole matched
    return [](const std::string&, const std::string&) { return true; };
}

CaseSensitiveFilter SearchFilterFactory::createCaseSensitiveFilter()
{
    if (options.caseSensitive)
    {
        return [](const std::string& text, const std::string& dest) {
            return dest.find(text) != std::string::npos;
        };
    }

    // case sensitive is not important
    return [](const std::string&, const std::string&) {
        return true;
    };
}

bool SearchFilterFactory::isBasicMatched(const std::string& text, const std::string& dest)
{
    const auto _dest = utils::toLower(dest);
    const auto _text = utils::toLower(text);
    return _dest.find(_text) != std::string::npos;
}
}