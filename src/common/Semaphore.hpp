#pragma once
#include <exception>
#include "Logger.hpp"

#ifdef __WINDOWS__
#include <windows.h>
#endif

namespace common{
class Semaphore
{
public:
    Semaphore(const std::string& name, const long initCount, const long maxCount)
    : name{name}, initCount{initCount}, maxCount{maxCount}
    {
        try
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
        catch(std::runtime_error e)
        {
            LOG_ERROR << e.what() << std::endl;
        #ifdef __DEBUG__
            LOG_ERROR << "Position:  " << __FILE__ << " : " << __FUNCTION__ << std::endl;  
        #endif
            exit(-1);
        }
    }

    ~Semaphore() 
    {
        CloseHandle(hdl);
    }

    const HANDLE getHandle() const
    {
        return hdl;
    }

    bool release()
    {
        return ReleaseSemaphore(hdl, 1, NULL);
    }

    DWORD wait()
    {
        return WaitForSingleObject(hdl, INFINITE);
    }

private:
    const std::string name;
    const long initCount;
    const long maxCount;
    HANDLE hdl;
};
}
