#ifndef FILE_WRITER_HPP
#define FILE_WRITER_HPP

#include <iostream>
#include <fstream>

class FileWriter
{
public:
	FileWriter(std::string fileName) : mFileName(fileName),mWriter(mFileName) {}
	FileWriter(const char* fileName) : mFileName(fileName),mWriter(mFileName) {}
	FileWriter() {}
	virtual ~FileWriter() 
	{
		close();
	}
	void open(std::string fileName)
	{
		mFileName = fileName;
		mWriter.open(mFileName);
	}
	void appendOpen(std::string fileName)
	{
		mFileName = fileName;
		mWriter.open(mFileName,std::ios::app);
	}
	void appendOpen(const char* fileName)
	{
		mFileName = fileName;
		mWriter.open(mFileName,std::ios::app);
	}
	void writeLine(std::string str)
	{
		mWriter << str << std::endl;
	}
	void write(std::string str)
	{
		mWriter << str;
	}
	void close()
	{
		if(mWriter.is_open())
		{
			mWriter.close();
		}
	}
	std::string getFileName()
	{
		return mFileName;
	}
private:
	std::string 	mFileName;
	std::ofstream 	mWriter;
};
#endif