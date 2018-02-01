#pragma once
#include <fstream>
#include <string>
#include "Logger.hpp"

namespace common {

class FileWriter
{
public:
	FileWriter(const std::string& fileName) : fileName(fileName)
    {
        try
        {
            writer.open(fileName, std::ofstream::trunc);
        }
        catch(std::ofstream::failure)
        {
            LOG_ERROR << "Open file " << fileName << "failed! \n";
            exit(-1);
        }
    }

    virtual ~FileWriter() 
    {
        if(writer.is_open())
        {
            writer.close();
        }
    }

    void writeLine(const std::string& str)
    {
        writer << str << "\n";
    }
    
    void write(const std::string& str)
    {
        writer << str;
    }

    const std::string getFileName() const
    {
        return fileName;
    }

private:
    std::string fileName;
    std::ofstream writer;
};
}
