#pragma once
#include "Result.hpp"
#include <iostream>
#include <sstream>

namespace output {

struct Conclusion {
    uint32_t foundFiles = 0;
    uint32_t foundLines = 0;
};

class ClgrResult : public Result {
public:
    ClgrResult() {}

    void GetAFileSearchResult(const std::string& filename) override {
        ++conclusion.foundFiles;
        std::cout << filename << std::endl;
    }

	void GetATextSearchResult(const std::string& filename, const std::vector<common::MatchedLine>& lines) override {
        ++conclusion.foundFiles;
        conclusion.foundLines += lines.size();
        std::stringstream ss;
        ss << ">>>" << filename << ":\n";
        for (const auto& line: lines) {
            ss << line.num << ": " << line.line << '\n';
        }
        std::cout << ss.str() << std::endl;
    }

	void SearchConclusion() override{
        std::cout << "Search End! Found files: " << conclusion.foundFiles;
        if (conclusion.foundFiles > 0 && conclusion.foundLines > 0) {
            std::cout << "    Found lines: " << conclusion.foundLines;
        }
        std::cout << std::endl;
    }
private:
    Conclusion conclusion;
};
}