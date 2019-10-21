#include "search/FileSearcher.hpp"
#include "search/TextSearcher.hpp"
#include "search/ClgrSearcher.hpp"
#include "common/MatchedLine.hpp"
#include "output/ClgrResult.hpp"
#include "args/Args.hpp"

int main(int argc, char** argv) {
    args::Args cmdParser(argc, argv);
    cmdParser.AddParameter("dir", "d", {"."}, "");
    cmdParser.AddParameter("file", "f", {}, "");
    cmdParser.AddParameter("text", "t", {}, "");
    cmdParser.AddParameter("ignorecase", "ic", {}, "");
    cmdParser.AddParameter("matchwholeword", "mww", {}, "");
    cmdParser.AddParameter("ignorefoldername", "ifn", {}, "");
    cmdParser.AddParameter("regular", "r", {}, "");
    cmdParser.AddParameter("help", "h", {}, "");
    std::map<std::string, args::Param> config = cmdParser.parse();

    output::ClgrResult res{};
    search::ClgrSearcher searcher(res);
    searcher.setIgnoreCase(config.at("ignorecase").isExist);
    searcher.setIgnoreFolderName(config.at("ignorefoldername").isExist);
    searcher.setMatchWholeWord(config.at("matchwholeword").isExist);
    searcher.setUseRegular(config.at("regular").isExist);
    auto dirs = config.at("dir").isExist ? config.at("dir").value : config.at("dir").defaultVal;
    auto files = config.at("file").isExist ? config.at("file").value : config.at("file").defaultVal;
    auto texts = config.at("text").isExist ? config.at("text").value : config.at("text").defaultVal;
    searcher.search(dirs, files, texts);
}