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

}
}