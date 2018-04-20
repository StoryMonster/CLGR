#pragma once
#include <string>
#include <vector>

namespace types
{

enum class SearchType
{
    file,
    text,
    help,
    version
};

struct SearchOptions
{
    bool caseSensitive = false;
    bool matchWholeWord = false;
};

struct SearchField
{
    std::string dir;
    std::vector<std::string> files{};
};
/*
SearchField::files:
    for test search, it helps to decrease the search field
    for file search, it's the files need to be searched
*/

struct SearchInfo
{
    SearchType type;
    std::string text;    //only for test search
    SearchField field;
    SearchOptions options;
};

}