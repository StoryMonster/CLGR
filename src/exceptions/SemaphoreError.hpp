#pragma once
#include <stdexcept>

namespace exceptions
{

class SemaphoreWaitError : public std::runtime_error
{
public:
    SemaphoreWaitError(const std::string& errLog) : std::runtime_error(errLog)
    {}
};

class SemaphoreInitError : public std::runtime_error
{
public:
    SemaphoreInitError(const std::string& errLog) : std::runtime_error(errLog)
    {}
};
}