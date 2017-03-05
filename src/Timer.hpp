#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <sstream>
#include <cassert>
#include <ctime>

class Timer
{
public:
	Timer() : mTimerIsRunning(false) {}
	virtual ~Timer() {}
	void start()
	{
		assert(!mTimerIsRunning);
		mStartClock = clock();
		mTimerIsRunning = true;
	}
	void stop()
	{
		assert(mTimerIsRunning);
		mStopClock = clock();
		mTimerIsRunning = false;
	}
	std::string pickupCurrentClock()
	{
		assert(mTimerIsRunning);
		clock_t cost = clock() - mStartClock;
		std::stringstream ss;
		if(cost < 1000)
		{
			ss << cost << "ms";
		}
		else
		{
			ss << cost/1000 << "s " << cost % 1000 << "ms" ;
		}
		return ss.str();
	}
	clock_t getCostTime()
	{
		assert(!mTimerIsRunning);
		assert(mStopClock >= mStartClock);
		return mStopClock - mStartClock;
	}
	std::string getCostTimeStringAdjustUnit()
	{
		clock_t cost = getCostTime();
		std::stringstream ss;
		if(cost < 1000)
		{
			ss << cost << "ms";
		}
		else
		{
			ss << cost/1000 << "s " << cost % 1000 << "ms" ;
		}
		return ss.str();
	}
	std::string getCurrentTime()
	{
		time_t ctm = time(NULL);
		struct tm *currentTime = localtime(&ctm);
		std::stringstream ss;
		ss << currentTime->tm_year + 1900 << "/" 
		   << currentTime->tm_mon + 1 << "/" 
		   << currentTime->tm_mday << "  "
		   << currentTime->tm_hour << ":"
		   << currentTime->tm_min << ":"
		   << currentTime->tm_sec;
		return ss.str();
	}
private:
	clock_t mStartClock;
	clock_t mStopClock;
	bool mTimerIsRunning;
};


#endif