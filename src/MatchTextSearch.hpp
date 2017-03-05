#ifndef MATCH_TEXT_SEARCH_HPP
#define MATCH_TEXT_SEARCH_HPP

#include <iostream>
#include <list>
#include <exception>
#include "FileReader.hpp"
#include "ErrorLog.hpp"

class MatchTextSearch
{
public:
	MatchTextSearch(FileReader& fd, std::string str) : mFd(fd),mFilter(str) {}
	virtual ~MatchTextSearch() {}
	void start()
	{
		while(!mFd.isEndOfFile())
		{
			std::string line = mFd.readLine();
			if(line.size() && std::string::npos != line.find(mFilter))
			{		
				mLstLines.push_back(mFd.getCurrentLineNumber());
			}
		}
	}
	std::list<unsigned int>& getLines()
	{
		return mLstLines;
	}
	bool isFindSuccess()
	{
		return (mLstLines.size() > 0);
	}
protected:
	FileReader& mFd;
	std::string mFilter;
	std::list<unsigned int> mLstLines;
};


#endif