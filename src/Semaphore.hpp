#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <windows.h>
#include <iostream>
#include <exception>
#include "ErrorLog.hpp"

class Semaphore
{
public:
	Semaphore(std::string name, long initialCount, long maximumCount) : mName(name),mInitCount(initialCount),mMaxCount(maximumCount)  
	{
		try
		{
			if(InitSemaphore() == false)
			{
				throw std::runtime_error("create semaphore error, and it may cause text search error!");
			}
			mHdl = open();
			if(mHdl == NULL)
			{
				throw std::runtime_error("open semaphore error, and it may cause text search error!");
			}
		}
		catch(std::runtime_error e)
		{
			ErrorLog	clgrLog;
			clgrLog.writeError(e.what());
			std::cerr << e.what() << std::endl;
		#ifdef _DEBUG
			std::cout << "position:  " <<__FILE__ << "::" <<__FUNCTION__ << std::endl;  
		#endif
			exit(-1);
		}
	}
	~Semaphore() 
	{
		CloseHandle(mHdl);
	}
	bool InitSemaphore()
	{
		mHdl = CreateSemaphore(NULL,mInitCount,mMaxCount,mName.c_str());
		if(mHdl == 0) return false;
		else if(ERROR_ALREADY_EXISTS == GetLastError())
		{
			CloseHandle(mHdl);
			return false;
		}
		else return true;
	}
	const HANDLE getHandle() const
	{
		return this->mHdl;
	}
	HANDLE open()
	{
		return OpenSemaphore(SEMAPHORE_ALL_ACCESS,false,mName.c_str());
	}
	bool release()
	{
		return ReleaseSemaphore(mHdl,1,NULL);
	}
	DWORD wait()
	{
		return WaitForSingleObject(mHdl,INFINITE);
	}
private:
	std::string mName;
	long mInitCount;
	long mMaxCount;
	HANDLE mHdl;
};
#endif