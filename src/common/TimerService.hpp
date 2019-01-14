#pragma once
#include <chrono>

namespace common
{
class TimerService
{
public:
    TimerService() {}
    
    double getPassedTime()
    {
        // return time unit is second
        return std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count();
    }


private:
    std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
};
}