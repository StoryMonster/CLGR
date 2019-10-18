#pragma once
#include <string>
#include <vector>
#include "../common/MatchedLine.hpp"

namespace output {

class Result {
public:
    virtual void GetAFileSearchResult(const std::string& filename) = 0;
	virtual void GetATextSearchResult(const std::string& filename, const std::vector<common::MatchedLine>& lines) = 0;
	virtual void SearchConclusion() = 0;
};
}