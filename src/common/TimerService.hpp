#pragma once
#include <chrono>

namespace common
{
class TimerService
{
public:
    TimerService()
    {
        startTime = std::chrono::system_clock::now();
    }
    
    double getPassedTime()
    {
        // return time unit is second
        return std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count();
    }


private:
    std::chrono::time_point<std::chrono::system_clock> startTime;
};
}