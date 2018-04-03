#include "Semaphore.hpp"
#include <stdexcept>

namespace common{

#ifdef __WINDOWS__
WindowsSemaphore::WindowsSemaphore(const std::string& name, const std::int32_t initCount, const std::int32_t maxCount)
{
    hdl = CreateSemaphore(NULL, initCount, maxCount, name.c_str());
    if(hdl == 0 || ERROR_ALREADY_EXISTS == GetLastError())
    {
        throw std::runtime_error("Create semaphore error, and it may cause text search error!");
    }
    hdl = OpenSemaphore(SEMAPHORE_ALL_ACCESS, false, name.c_str());
    if(!hdl)
    {
        throw std::runtime_error("Open semaphore error, and it may cause text search error!");
    }
}

WindowsSemaphore::~WindowsSemaphore() 
{
    CloseHandle(hdl);
}

void WindowsSemaphore::release()
{
    ReleaseSemaphore(hdl, 1, NULL);
}

void WindowsSemaphore::wait()
{
    WaitForSingleObject(hdl, INFINITE);
}

#else
LinuxSemaphore::LinuxSemaphore(sem_t& sem, const std::uint32_t initCount)
: sem(sem)
{
    if (0 != sem_init(&sem, 0, initCount))
    {
        throw std::runtime_error("Create semaphore error, and it may cause text search error!");
    }
}

LinuxSemaphore::~LinuxSemaphore()
{
    sem_destroy(&sem);
}

void LinuxSemaphore::wait()
{
    sem_wait(&sem);
}

void LinuxSemaphore::release()
{
    sem_post(&sem);
}
#endif
}