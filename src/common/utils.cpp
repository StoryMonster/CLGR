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
    for (const auto ch : line)
    {
        if(ch == 0x00 || ch == 0x01 || ch == 0x02 || ch == 0x03 || ch == 0x04 ||
           ch == 0x05 || ch == 0x06 || ch == 0x07)
        return true;
    }
    return false;
}

}
}