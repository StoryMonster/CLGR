#pragma once
#include "common/Logger.hpp"

class VersionControler
{
public:
    static void showVersion()
    {
        LOG_INFO << "\n";
        LOG_INFO << "CLGR-V3.0      2018/1/31  dochen\n";
        LOG_INFO << "This version provides a more convinient function, "
                 << "you can find text in specific directories and specific files\n";
    }
};