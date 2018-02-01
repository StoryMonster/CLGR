#include "common/Logger.hpp"
#include "common/CommandLineParser.hpp"
#include "types/SearchInfo.hpp"
#include "FileSearcher.hpp"
#include "TextSearcher.hpp"
#include "HelpDisplayer.hpp"
#include "VersionControler.hpp"

int main(int argc, char *argv[])
{
    common::CommandLineParser parser(argc, argv);
    const auto cmdLineInfo = parser.parse();

    if (cmdLineInfo.type == types::SearchType::file)
    {
        FileSearcher searcher(cmdLineInfo.field);
        searcher.search();
    }
    else if (cmdLineInfo.type == types::SearchType::text)
    {
        TextSearcher searcher(cmdLineInfo.text, cmdLineInfo.field);
        searcher.search();
    }
    else if (cmdLineInfo.type == types::SearchType::version)
    {
        VersionControler::showVersion();
    }
    else
    {
        HelpDisplayer::display();
    }
}