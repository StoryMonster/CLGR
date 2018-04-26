#include "src/common/CommandLineParser.hpp"
#include "src/types/SearchInfo.hpp"
#include "FileSearcher.hpp"
#include "TextSearcher.hpp"
#include "HelpDisplayer.hpp"
#include "VersionControler.hpp"
#include <chrono>
#include <iostream>

int main(int argc, char *argv[])
{
    const auto startTime = std::chrono::system_clock::now();
    common::CommandLineParser parser(argc, argv);
    const auto cmdLineInfo = parser.parse();

    if (cmdLineInfo.type == types::SearchType::file)
    {
        FileSearcher searcher(cmdLineInfo.field, cmdLineInfo.options);
        searcher.search();
        const auto endTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> elapsed_seconds = endTime - startTime;
        std::cout << "Time used: " << elapsed_seconds.count() << "s" << std::endl;
    }
    else if (cmdLineInfo.type == types::SearchType::text)
    {
        TextSearcher searcher(cmdLineInfo.text, cmdLineInfo.field, cmdLineInfo.options);
        searcher.search();
        const auto endTime = std::chrono::system_clock::now();
        const std::chrono::duration<double> elapsed_seconds = endTime - startTime;
        std::cout << "Time used: " << elapsed_seconds.count() << "s" << std::endl;
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
