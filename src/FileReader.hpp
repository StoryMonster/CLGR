#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <iostream>
#include <fstream>

class FileReader
{
public:
	FileReader(std::string fileName) : mFileName(fileName),mIn(mFileName),mLine(0),mIsEndOfFile(false) {}
	FileReader(const char* fileName) : mFileName(fileName),mIn(mFileName),mLine(0),mIsEndOfFile(false) {}
	FileReader() : mLine(0),mIsEndOfFile(false) {}
	~FileReader()
	{
		close();
	}
	void open(std::string fileName)
	{
		mFileName = fileName;
		mIn.open(fileName);
	}
	void close()
	{
		if(mIn.is_open())
		{
			mIn.close();
		}
		mLine = 0;
	}
	std::string getFileName()
	{
		return mFileName;
	}
	std::string readLine()
	{
		std::string res("");
		if(!std::getline(mIn,res))
		{
			mIsEndOfFile = true;
		}
		++mLine;
		return res;
	}
	bool isEndOfFile()
	{
		return mIsEndOfFile;
	}
	const unsigned int getCurrentLineNumber() const
	{
		return mLine;
	}
private:
	std::string mFileName;
	std::ifstream mIn;
	unsigned int mLine;
	bool mIsEndOfFile;
};

#endif