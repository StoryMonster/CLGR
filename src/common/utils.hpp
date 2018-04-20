#pragma once
#include <cstdint>
#include <string>

namespace common {
namespace utils {

std::uint32_t getNecessaryThreadNumbers(const std::uint32_t);
std::string toLower(const std::string&);
bool isBinaryLine(const std::string&);
bool isWordWholeMatched(const std::string&, const std::string&);
}
}
