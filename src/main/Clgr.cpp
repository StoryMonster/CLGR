#include "src/common/CommandLineParser.hpp"
#include "src/types/SearchInfo.hpp"
#include "FileSearcher.hpp"
#include "TextSearcher.hpp"
#include "HelpDisplayer.hpp"
#include "VersionControler.hpp"
#include "src/common/TimerService.hpp"
#include "src/exceptions/ParserError.hpp"
#include <iostream>

int main(int argc, char *argv[]) try
{
    common::TimerService timerService;
    common::CommandLineParser parser(argc, argv);
    const auto cmdLineInfo = parser.parse();

    if (cmdLineInfo.type == types::SearchType::file)
    {
        FileSearcher searcher(cmdLineInfo.field, cmdLineInfo.options);
        searcher.search();
        std::cout << "Time used: " << timerService.getPassedTime() << 's' << std::endl;
    }
    else if (cmdLineInfo.type == types::SearchType::text)
    {
        TextSearcher searcher(cmdLineInfo.text, cmdLineInfo.field, cmdLineInfo.options);
        searcher.search();
        std::cout << "Time used: " << timerService.getPassedTime() << 's' << std::endl;
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
catch(const exceptions::ParserError& e)
{
    std::cout << e.what() << std::endl;
    HelpDisplayer::display();
}
