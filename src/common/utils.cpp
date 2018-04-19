#include "utils.hpp"
#include "src/common/DeviceManager.hpp"

namespace common {
namespace utils {

std::uint32_t getNecessaryThreadNumbers(const std::uint32_t needMaxNums)
{
#ifdef __WINDOWS__
    auto devInfo = common::WindowsDeviceManager();
#else
    auto devInfo = common::LinuxDeviceManager();
#endif
    const std::uint32_t supportMaxThreadNums = devInfo.getProcessorNumbers();
    return (needMaxNums < supportMaxThreadNums) ? needMaxNums : supportMaxThreadNums;
}

std::string toLower(const std::string& str)
{
    std::string lowerStr(str);
    for (auto& ch : lowerStr)
    {
        if (ch <= 'Z' && ch >= 'A')
        {
            ch = ch - 'A' + 'a';
        }
    }
    return lowerStr;
}

bool isBinaryLine(const std::string& line)
{
    for (const auto& ch : line)
    {
        if (ch < 0x08) { return true; }
    }
    return false;
}

}
}