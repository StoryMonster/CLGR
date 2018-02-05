#pragma once

class VersionControler
{
public:
    static void showVersion()
    {
        LOG_INFO << "\n";
        LOG_INFO << "CLGR-V3.1      2018-02-05  dochen\n";
        LOG_INFO << "This version provides a more convinient function, "
                 << "you can find text in specific directories and specific files\n";
    }
};