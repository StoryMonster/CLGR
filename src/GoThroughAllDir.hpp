#ifndef GO_THROUGH_ALL_DIR_HPP
#define GO_THROUGH_ALL_DIR_HPP

#include <windows.h>
#include <iostream>
#include <list>
#include <queue>
#include <stdio.h>
#include <io.h>
#include <cstring>
#include <algorithm>
#include "Timer.hpp"
#include "FileInfo.hpp"

extern std::list<FileInfo> 		globalFileList;
extern std::string	theAppName;

class GoThroughAllDir
{
public:
	GoThroughAllDir(std::string str) : mDirPath(str),mStrFilter(".") {}
	GoThroughAllDir() : mDirPath("."),mStrFilter("\0") {}
	virtual ~GoThroughAllDir() {}
	void start()
	{
		Timer mTimer;
		mTimer.start();
		traversal(mDirPath);
		mTimer.stop();
	#ifdef _DEBUG
		std::cout << "Traversal folder cost: " << mTimer.getCostTimeStringAdjustUnit() << std::endl;
	#endif
	}
	void traversal(std::string path)
	{
		struct _finddata_t fileInfo;
		std::queue<std::string> folders;
		folders.push(path);
		while(folders.size())
		{
			path = folders.front();
			folders.pop();
			long hFile = _findfirst((path + "/*").c_str(),&fileInfo);
			if(hFile != -1)
			{
				do
				{
					if(fileInfo.attrib &  _A_SUBDIR)
					{
						if(strcmp(fileInfo.name,".") !=0 && strcmp(fileInfo.name,"..") != 0)
							folders.push(path + "\\" + fileInfo.name);
					}
					else
					{
						if(theAppName.compare(fileInfo.name) != 0 and std::string(fileInfo.name).find(mStrFilter) != std::string::npos)
						{
							globalFileList.push_back(FileInfo(path + "\\" + fileInfo.name,std::string(fileInfo.name),fileInfo.size));
						}
					}
				}while(_findnext(hFile,&fileInfo) == 0);
				_findclose(hFile);
			}
		}
	}
	void setTargetDir(std::string dir)
	{
		mDirPath = dir;
	}
	void setFilter(std::string filter)
	{
		mStrFilter = filter;
	}
protected:
	std::string mDirPath;
	std::string mStrFilter;
};

#endif