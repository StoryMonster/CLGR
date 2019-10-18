#include "search/FileSearcher.hpp"
#include "search/TextSearcher.hpp"
#include "search/ClgrSearcher.hpp"
#include "common/MatchedLine.hpp"
#include "args/Args.hpp"

int main(int argc, char** argv) {
    args::Args cmdParser(argc, argv);
    cmdParser.AddParameter("dir", "d", {}, "");
    cmdParser.AddParameter("file", "f", {}, "");
    cmdParser.AddParameter("text", "t", {}, "");
    cmdParser.AddParameter("ignorecase", "ic", {}, "");
    cmdParser.AddParameter("matchwholeword", "mww", {}, "");
    cmdParser.AddParameter("ignorefoldername", "ifn", {}, "");
    cmdParser.AddParameter("regular", "r", {}, "");
    cmdParser.AddParameter("help", "h", {}, "");
    std::map<std::string, args::Param> config = cmdParser.parse();

    search::ClgrSearcher searcher;
    searcher.setIgnoreCase(config.at("ignorecase").isExist);
    searcher.setIgnoreFolderName(config.at("ignorefoldername").isExist);
    searcher.setMatchWholeWord(config.at("matchwholeword").isExist);
    searcher.setUseRegular(config.at("regular").isExist);
    searcher.search(config.at("dir").value, config.at("file").value, config.at("text").value);
}