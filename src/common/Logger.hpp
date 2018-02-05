#pragma once
#include <iostream>
#include <iomanip>

namespace common {

enum class LogLevel
{
    info,
    warn,
    error,
    debug
};

class Logger
{
public:
    Logger(const LogLevel level, std::ostream& os=std::cout)
    : level{level}, os(os)
    {}

    template <typename T>
    std::ostream& operator<<(const T& stream)
    {
        if (level == LogLevel::warn)
        {
            os << "warning: ";
        }
        else if  (level == LogLevel::error)
        {
            os << "error: ";
        }
        os << stream;
        return os;
    }

private:
    LogLevel level;
    std::ostream& os;
};
}

auto LOG_INFO = common::Logger(common::LogLevel::info);
auto LOG_WARN = common::Logger(common::LogLevel::warn);
auto LOG_ERROR = common::Logger(common::LogLevel::error);
auto LOG_DEBUG = common::Logger(common::LogLevel::debug);
