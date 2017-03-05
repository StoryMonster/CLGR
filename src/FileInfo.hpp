#ifndef FILE_INFO_HPP
#define FILE_INFO_HPP

#include <iostream>
#include <list>

class FileInfo
{
public:
	FileInfo(std::string name,unsigned int size, std::list<unsigned int> lst) : mName(name),mSize(size),mLstLines(lst) {}
	FileInfo(std::string name,unsigned int size) : mName(name),mSize(size) {}
	FileInfo(std::string path, std::string name,unsigned int size) : mName(name),mSize(size),mPath(path) {}
	FileInfo(std::string name) : mName(name),mSize(0) {}
	virtual ~FileInfo() {}
	
	void setName(const std::string& name)
	{
		mName = name;
	}
	std::string getName() const
	{
		return mName;
	}
	void setSize(unsigned int size) 
	{
		mSize = size;
	}
	unsigned int getSize() const
	{
		return mSize;
	}
	void setPath(std::string path)
	{
		mPath = path;
	}
	std::string getPath() const
	{
		return this->mPath;
	}
	void addOneLine(unsigned int lineNum)
	{
		mLstLines.push_back(lineNum);
	}
	void addLines(std::list<unsigned int>& lst)
	{
		for(auto& item : lst)
		{
			mLstLines.push_back(item);
		}
	}
	friend std::ostream& operator<<(std::ostream& os, const FileInfo& fi)
	{
		os << fi.mName << "   " << fi.mSize << " Bytes";
		return os;
	}
	void clear()
	{
		mLstLines.clear();
	}
	std::list<unsigned int>& getMatchedLines()
	{
		return this->mLstLines;
	}
	unsigned int getMatchedLinesCount() const
	{
		return mLstLines.size();
	}
	
private:
	std::string      mName;
	unsigned int     mSize;
	std::string 	 mPath;
	std::list<unsigned int>   mLstLines;					//保存关键字在该文件中的行号
};
#endif