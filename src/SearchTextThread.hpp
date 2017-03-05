#ifndef SEARCH_THREAD_HPP
#define SEARCH_THREAD_HPP

#include <windows.h>
#include <iostream>
#include <list>
#include <map>
#include <exception>
#include <sstream>
#include "StandardThread.hpp"
#include "FileReader.hpp"
#include "MatchTextSearch.hpp"
#include "Timer.hpp"
#include "FileInfo.hpp"
#include "Semaphore.hpp"

class SearchTextThread : public StandardThread
{
public:
	SearchTextThread(std::string str) : mTargetStr(str){}
	SearchTextThread()  {}
	virtual ~SearchTextThread() 
	{
	}
	void setTargetString(std::string str)
	{
		mTargetStr = str;
	}
	virtual void run()
	{
		extern std::list<FileInfo> 		globalFileList;
		extern std::list<FileInfo> 	    globalMatchResult;
		mTimer.start();
		Timer tm;
		while(globalFileList.size() > 0)
		{
			sem.wait();
			auto file = globalFileList.front();
			globalFileList.pop_front();
			sem.release();
			tm.start();
			FileReader fd(file.getPath());
			MatchTextSearch mts(fd,mTargetStr);
			mts.start();
			fd.close();
			tm.stop();
		#ifdef _DEBUG
			std::cout << "Matching file: " << file.getPath() << std::endl;
			mLstSearchedFilesAndTime.insert(make_pair(file.getPath(),tm.getCostTimeStringAdjustUnit()));
		#endif
			if(mts.isFindSuccess())
			{
				file.addLines(mts.getLines());
				globalMatchResult.push_back(file);
			}		
		}
		mTimer.stop();
	}
	void showSearchInfo()
	{
		std::cout << "Thread " <<(int)getHandle() <<" cost: "<< mTimer.getCostTimeStringAdjustUnit() << std::endl;
		for(auto& item : mLstSearchedFilesAndTime)
		{
			std::cout << "    " << item.first << "-----" << item.second << std::endl;
		}
	}
public:
	static Semaphore sem;
protected:
	std::string 						mTargetStr;
	Timer 								mTimer;
	std::map<std::string,std::string>   mLstSearchedFilesAndTime;
};
Semaphore SearchTextThread::sem("name",1,1);
#endif