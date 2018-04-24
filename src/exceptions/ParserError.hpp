#pragma once
#include <stdexcept>

namespace exceptions
{

class ParserError : public std::runtime_error
{
public:
    ParserError(const std::string& errLog) : std::runtime_error(errLog)
    {}
};
}