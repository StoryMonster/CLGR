#pragma once
#include <iostream>
#include <string>
#include <cstdint>

namespace types{

class FileInfo
{
public:
    FileInfo(const std::string& fileName, const std::string& filePath, const std::uint32_t size)
    : fileName{fileName}, filePath{filePath}, fileSize{size}
    {
    #ifdef __WINDOWS__
        completePath = filePath + "\\" + fileName;
    #else
        completePath = filePath + "/" + fileName;
    #endif
    }

    virtual ~FileInfo() {}

    inline std::string getfileName() const
    {
        return fileName;
    }

    inline std::uint32_t getSize() const
    {
        return fileSize;
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
        os << fi.completePath << "    " << fi.fileSize << " bytes";
        return os;
    }

private:
    std::string fileName;
    std::string filePath;
    std::uint32_t fileSize;
    std::string completePath;
};
}
