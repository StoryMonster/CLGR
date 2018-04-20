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

bool isWordWholeMatched(const std::string& word, const std::string& str)
{
    const auto position = str.find(word);
    if (position == std::string::npos) { return false; }
    if (position != 0)
    {
        if ((str[position-1] >= '0' && str[position-1] <= '9') ||
            (str[position-1] >= 'A' && str[position-1] <= 'Z') ||
            (str[position-1] >= 'a' && str[position-1] <= 'z'))
        {
            return false;
        }
    }
    const auto endPos = position + word.size();
    if (endPos < str.size())
    {
        if ((str[endPos] >= '0' && str[endPos] <= '9') ||
            (str[endPos] >= 'A' && str[endPos] <= 'Z') ||
            (str[endPos] >= 'a' && str[endPos] <= 'z'))
        {
            return false;
        }
    }
    return true;
}
}
}