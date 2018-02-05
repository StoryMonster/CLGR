#pragma once
#include <cstdint>

#ifdef __WINDOWS__
#include <windows.h>
#else
#include "FileReader.hpp"
#endif

namespace common{

class DeviceManager
{
public:
    virtual const std::uint32_t getProcessorNumbers() = 0;
};

#ifdef __WINDOWS__
class WindowsDeviceManager : public DeviceManager
{
public:
    WindowsDeviceManager()
    {
        memset(&systemInfo, 0, sizeof(systemInfo));
        GetSystemInfo(&systemInfo);
    }

    const std::uint32_t getProcessorNumbers() override
    {
        return static_cast<std::uint32_t>(systemInfo.dwNumberOfProcessors);
    }
private:
    SYSTEM_INFO systemInfo;
};

#else
class LinuxDeviceManager : public DeviceManager
{
public:
    LinuxDeviceManager()
    {
    }

    const std::uint32_t getProcessorNumbers() override
    {
        const auto deviceInfoFile = "/proc/cpuinfo";
        FileReader reader(deviceInfoFile);
        std::uint32_t processorCounter = 0;
        while (!reader.isReadToEnd())
        {
            if (0 == reader.readLine().size())
            {
                ++processorCounter;
            }
        }
        return processorCounter;
    }
};
#endif

}