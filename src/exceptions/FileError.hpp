#pragma once
#include <stdexcept>

namespace exceptions
{

class FileError : public std::runtime_error
{
public:
    FileError(const std::string& errLog) : std::runtime_error(errLog) {}
};

class OpenFileError : public FileError
{
public:
    OpenFileError(const std::string& fileName) : FileError(std::string("Open ") + fileName + std::string("Error"))
    {}
};
}