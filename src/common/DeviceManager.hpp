#pragma once
#include <cstdint>

#ifdef __WINDOWS__
#include <windows.h>
#endif

namespace common{

class DeviceManager
{
public:
    virtual const std::uint32_t getProcessorNumbers() = 0;
};

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

class LinuxDeviceManager : public DeviceManager
{
public:
    LinuxDeviceManager()
    {
    }

    const std::uint32_t getProcessorNumbers() override
    {
        return 4;      //TODO: complete later
    }

};
}