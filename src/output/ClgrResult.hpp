#pragma once
#include "Result.hpp"
#include <iostream>
#include <sstream>
#include <chrono>
//#include <mutex>

namespace output {

struct Conclusion {
    uint32_t foundFiles = 0;
    uint32_t foundLines = 0;
};

class ClgrResult : public Result {
public:
    ClgrResult(): startTimePoint{std::chrono::steady_clock::now()} {}

    void GetAFileSearchResult(const std::string& filename) override {
        //mt.lock();
        ++conclusion.foundFiles;
        std::cout << filename << std::endl;
        //mt.unlock();
    }

	void GetATextSearchResult(const std::string& filename, const std::vector<common::MatchedLine>& lines) override {
        std::stringstream ss;
        ss << ">>>" << filename << ":\n";
        for (const auto& line: lines) {
            ss << line.num << ": " << line.line << '\n';
        }
        //mt.lock();
        ++conclusion.foundFiles;
        conclusion.foundLines += lines.size();
        std::cout << ss.str() << std::endl;
        //mt.unlock();
    }

	void SearchConclusion() override{
        std::chrono::steady_clock::time_point endTimePoint = std::chrono::steady_clock::now();
        std::cout << "Search End! Found files: " << conclusion.foundFiles;
        if (conclusion.foundFiles > 0 && conclusion.foundLines > 0) {
            std::cout << "    Found lines: " << conclusion.foundLines;
        }
        std::cout << std::endl;
        std::cout << "Time cost: " << std::chrono::duration_cast<std::chrono::duration<double>>(endTimePoint - startTimePoint).count() << "s" << std::endl;
    }
private:
    Conclusion conclusion{};
    std::chrono::steady_clock::time_point startTimePoint;
    //std::mutex mt{};
};
}