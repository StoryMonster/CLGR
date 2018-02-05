#pragma once
#include <cstdint>
#include <string>

#ifdef __WINDOWS__
#include <windows.h>
#else
#include <semaphore.h>
#endif

namespace common{

class Semaphore
{
public:
    virtual void wait() = 0;
    virtual void release() = 0;
};

#ifdef __WINDOWS__
class WindowsSemaphore : public Semaphore
{
public:
    WindowsSemaphore(const std::string&, const std::int32_t initCount = 1, const std::int32_t maxCount = 1);
    virtual ~WindowsSemaphore();
    void wait() override;
    void release() override;
private:
    HANDLE hdl;
};

#else
class LinuxSemaphore : public Semaphore
{
public:
    LinuxSemaphore(sem_t&, const std::uint32_t initCount = 1);
    virtual ~LinuxSemaphore();
    void wait() override;
    void release() override;
private:
    sem_t& sem;
};
#endif
}
