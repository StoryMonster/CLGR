#pragma once
#include <iostream>
#include <string>
#include <cstdint>

namespace types{

class FileInfo
{
public:
    FileInfo(const std::string& fileName, const std::string& filePath)
    : fileName{fileName}, filePath{filePath}
    {
    #ifdef __WINDOWS__
        completePath = filePath + "\\" + fileName;
    #else
        completePath = filePath + "/" + fileName;
    #endif
    }

    inline std::string getfileName() const
    {
        return fileName;
    }

    inline std::string getPath() const
    {
        return filePath;
    }

    inline std::string getCompletePath() const
    {
        return completePath;
    }

    friend std::ostream& operator<<(std::ostream& os, const FileInfo& fi)
    {
        os << fi.completePath;
        return os;
    }

private:
    std::string fileName;
    std::string filePath;
    std::string completePath;
};
}
