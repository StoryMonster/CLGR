#ifndef MATCH_FILE_SEARCH_HPP
#define MATCH_FILE_SEARCH_HPP

#include <iostream>
#include <list>
#include "FileInfo.hpp"
#include "GoThroughAllDir.hpp"

extern std::list<FileInfo> 		globalFileList;
extern std::list<FileInfo> 	    globalMatchResult;

class MatchFileSearch
{
public:
	MatchFileSearch(std::string str) : mStrFilter(str){}
	virtual ~MatchFileSearch() {}
	void start()
	{
		for(auto& item : globalFileList)
		{
			if(std::string::npos != item.getName().find(mStrFilter))
			{
			#ifdef _DEBUG
				std::cout << "             "  <<item.getPath() << std::endl;
			#endif
				globalMatchResult.push_back(item);
			}
			
		}
	}
	
private:
	std::string mStrFilter;
};


#endif