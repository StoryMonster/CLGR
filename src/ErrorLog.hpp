#ifndef ERROR_LOG_HPP
#define ERROR_LOG_HPP

#include <iostream>
#include <sstream>
#include "FileWriter.hpp"
#include "Timer.hpp"

static const std::string logFileName(".\\err.log");
class ErrorLog : public FileWriter
{
public:
	ErrorLog() 
	{
		appendOpen(logFileName);
	}
	virtual ~ErrorLog() {}
	void openLog()
	{
		appendOpen(logFileName);
	}
	void writeError(std::string str)
	{
	#ifdef _DEBUG
		std::cout << "Error: " << str << std::endl;
	#endif
		std::stringstream ss;
		ss.fill(' ');
		ss.width(50);
		ss << "Error: " << str;
		writeLine(ss.str() + "    " + mTimer.getCurrentTime());
	}
	void writeWarn(std::string str)
	{
	#ifdef _DEBUG
		std::cout << "Warning: " << str << std::endl;
	#endif
		std::stringstream ss;
		ss.fill(' ');
		ss.width(50);
		ss << "Warning: " << str;
		writeLine(ss.str() + "    " + mTimer.getCurrentTime());
	}
private:
	Timer mTimer;
};
#endif