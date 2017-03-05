#ifndef PARSE_COMMAND_LINE_HPP
#define PARSE_COMMAND_LINE_HPP

#include <iostream>
#include <list>
#include <cstring>

class ParseCommandLine
{
public:
	ParseCommandLine(int num,std::list<std::string>& lst) : mSearchHelp(false), mLstParam(lst), mTargetDir(".")  {}
	std::list<std::string> parse()
	{
		for(std::list<std::string>::iterator it = mLstParam.begin(); it != mLstParam.end(); ++it)
		{
			std::list<std::string>::iterator temp = it;
			if(it->compare("-f") == 0 || it->compare("-F") == 0)
			{
				mTargetFile = *(++temp);
			}
			else if(it->compare("-t") == 0 || it->compare("-T") == 0)
			{
				mTargetText = *(++temp);
			}
			else if(it->compare("-d") == 0 || it->compare("-D") == 0)
			{
				mTargetDir = *(++temp);
			}
			else if(it->compare("-h") == 0 || it->compare("-H") == 0)
			{
				mSearchHelp = true;
			}
			else ;
		}
		return mLstParam;
	}
	bool isSearchFile()
	{
		return (mTargetFile.size() > 0 && mTargetText.size() == 0);
	}
	bool isSearchText()
	{
		return (mTargetText.size() > 0);
	}
	bool isSearchHelp()
	{
		return mSearchHelp;
	}
	bool isSearchTextFromSpecificFile()
	{
		return (mTargetFile.size() > 0 && mTargetText.size() > 0);
	}
	std::string getTargetFile()
	{
		return (mTargetFile.size() > 0) ? mTargetFile : "";
	}
	std::string getTargetText()
	{
		return (mTargetText.size() > 0) ? mTargetText : "";
	}
	std::string getTargetDir()
	{
		return this->mTargetDir;
	}
private:
	bool    mSearchHelp;
	std::list<std::string>& mLstParam;
	std::string mTargetFile;
	std::string mTargetText;
	std::string mTargetDir;
};


#endif