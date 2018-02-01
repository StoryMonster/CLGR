#pragma once
#include "common/Logger.hpp"

class HelpDisplayer
{
public:
    static void display()
    {
        LOG_INFO << "\n";
        LOG_INFO << "help for CLGR:\n";
        LOG_INFO << "-t=<text>    to specify text needs to search\n";
        LOG_INFO << "-f=<file>    to specify file needs to search, if "
                 << "text is specified, it means to search text in this file\n";
        LOG_INFO << "-d=<dir>     to specify where to search, default value is current directory\n";
        LOG_INFO << "--help       to show helps\n";
        LOG_INFO << "--version    to show CLGR version\n"; 
    }
};