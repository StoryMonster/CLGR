#pragma once
#include <iostream>

class HelpDisplayer
{
public:
    static void display()
    {
        std::cout << "\n";
        std::cout << "help for CLGR:\n";
        std::cout << "-t=<text>    to limit text search field\n";
        std::cout << "-f=<file>    to limit text and file search field\n";
        std::cout << "-d=<dir>     to specify where to start searching, default value is current directory\n";
        std::cout << "--help       to show helps\n";
        std::cout << "--version    to show CLGR version\n";
        std::cout << std::endl;
    }
};