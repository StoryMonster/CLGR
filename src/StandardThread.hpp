#ifndef STANDARD_THREAD_HPP
#define STANDARD_THREAD_HPP

#include <windows.h>
#include <process.h>
#include <iostream>

class StandardThread
{
public:
	StandardThread() {}
	virtual ~StandardThread()
	{
		//CloseHandle(mHdl);
		_endthreadex(0);
	}
	static int dispatchFunction(void *param)
	{
		StandardThread* p = (StandardThread*)param;
		p->run();
		return 0;
	}
	void start()
	{
		mHdl = (HANDLE)(_beginthreadex(NULL,0,(unsigned int (__stdcall *)(void *))dispatchFunction,this,0,0));
		if(mHdl == 0)
		{
			std::cout << "Create thread failed!" << std::endl;
		}
	}
	HANDLE getHandle()
	{
		return mHdl;
	}
	void joinThread()
	{
		WaitForSingleObject(mHdl, INFINITE);
	}
	virtual void run(void) = 0;
protected:
	HANDLE mHdl;
};
#endif