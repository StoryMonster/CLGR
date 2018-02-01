#pragma once
#include "Logger.hpp"
#include <fstream>
#include <cstdint>

namespace common {

class FileReader
{
public:
    FileReader(std::string fileName) : fileName{fileName}, lineNumber{0}
    {
        try
        {
            reader.open(fileName);
        }
        catch(std::ofstream::failure)
        {
            LOG_ERROR << "Open file " << fileName << "failed! \n";
            exit(-1);
        }
    }

    virtual ~FileReader()
	{
        if(reader.is_open())
        {
            reader.close();
        }
    }
    
    const std::string readLine()
    {
        if (isReadToEnd())
        {
        	LOG_WARN << "File reader has read to the end of file!";
            return "";
        }
        std::string res;
        std::getline(reader, res);
        ++lineNumber;
        return res;
    }

    const std::uint32_t getLineNumber() const
    {
        return lineNumber;
    }
    
    const std::string getFileName() const
    {
        return fileName;
    }

    const bool isReadToEnd()
    {
        return reader.eof();
    }

private:
    std::string fileName;
    std::ifstream reader;
    std::uint32_t lineNumber;
};
}
