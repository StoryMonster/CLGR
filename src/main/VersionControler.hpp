#pragma once
#include <iostream>

class VersionControler
{
public:
    static void showVersion()
    {
        std::cout << "\n";
        std::cout << "CLGR-V3.2      2018-04-03  dochen\n";
        std::cout << "This version is to improve clgr's file search speed" << std::endl;
    }
};