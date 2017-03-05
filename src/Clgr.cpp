#include <iostream>
#include <exception>
#include <sstream>
#include <list>
#include <string>
#include <algorithm>
#include <cassert>
#include "ParseCommandLine.hpp"
#include "SearchTextThread.hpp"
#include "MatchFileSearch.hpp"
#include "GoThroughAllDir.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "Surface.hpp"
#include "Timer.hpp"
#include "FileInfo.hpp"
#include "ErrorLog.hpp"

std::list<FileInfo> 		globalFileList;
std::list<FileInfo> 	    globalMatchResult;
std::string					theAppName;

const std::string appVersion = "V2.1";
const std::string testFileName = "TestData_" + appVersion + ".txt";
const std::string resultFileName = ".\\result.txt";

class Clgr
{
public:
	Clgr(std::string dir) : mTargetDir(dir) , mGtad(mTargetDir) {}
	Clgr() : mTargetDir("."),mGtad(mTargetDir) {}
	void setTargetFile(std::string str)
	{
		mTargetFile = str;
	}
	void setTargetText(std::string str)
	{
		mTargetText = str;
	}
	void setTargetDir(std::string str)
	{
		mTargetDir = str;
		mGtad.setTargetDir(mTargetDir);
	}
	void searchFile()
	{
		assert(mTargetFile.size() > 0);
		std::cout << "Now, start to match file "<< mTargetFile << ", please wait..." <<std::endl;
		MatchFileSearch mfs(mTargetFile);
		mTimer.start();
		if(globalFileList.size() == 0)
		{
			mGtad.setFilter(mTargetFile);
			mGtad.start();
			for(auto item : globalFileList)
			{
				globalMatchResult.push_back(item);
			}
		}
		else
		{
			mfs.start();
		}
		mTimer.stop();
		mStrCostTime = mTimer.getCostTimeStringAdjustUnit();
		std::cout << "Matched file amount: " << globalMatchResult.size() << std::endl;
		std::cout << "The search cost "      << mStrCostTime << std::endl; 
	#ifdef _DEBUG
		recordTestData("-f");
	#endif
		recordFileSearchResultIntoFile();
		std::cout << "\nThe search result is saving into file result/RESULT.txt!" << std::endl;
		system(resultFileName.c_str());
		turnResultAsSearchField();
		operationAfterSearch();
	}
	void searchText()
	{
		assert(mTargetText.size() > 0);
		std::cout << "Now, start to match text \""<< mTargetText << "\", please wait..." <<std::endl;
		dispatchThreadWork();
		std::cout << "Matched file amount: " << globalMatchResult.size() << std::endl;
		std::cout << "The search cost " << mStrCostTime << std::endl;
	#ifdef _DEBUG
		recordTestData("-t");
	#endif
		recordTextSearchResultIntoFile();
		std::cout << "\nThe search result is saving into file result/RESULT.txt!" << std::endl;
		system(resultFileName.c_str());
		turnResultAsSearchField();
		operationAfterSearch();	
	}
	void help()
	{
		mSurface.showHelpGuide();
	}
	void operationAfterSearch()
	{
		if(!mSurface.noticeNextSearch()) return ;
		mSurface.clearScreen();
		std::string option;
		std::string targetStr;
		mSurface.inputNewKeyword(option,targetStr);
		if(option == "-f" || option == "-F")
		{
			mTargetFile = targetStr;
			searchFile();
		}
		else if(option == "-t" || option == "-T")
		{
			mTargetText = targetStr;
			searchText();
		}
		else
		{
			help();
		}
	}
	void dispatchThreadWork()
	{
		mTimer.start();
		if(globalFileList.size() == 0)
		{
			mGtad.start();
		}
		std::cout << "Total search file amount: " << globalFileList.size() << std::endl;
		int iRealNeedThreadCount = (globalFileList.size() < SEARCH_TEXT_THREAD_COUNT) ? globalFileList.size() : SEARCH_TEXT_THREAD_COUNT;
		for(int i = 0; i < iRealNeedThreadCount; ++i)
		{
			th[i].setTargetString(mTargetText);
			th[i].start();
		}
		for(int i = 0; i < iRealNeedThreadCount; ++i)
		{
			th[i].joinThread();
		}
		CloseHandle(SearchTextThread::sem.getHandle());
		mTimer.stop();
		mStrCostTime = mTimer.getCostTimeStringAdjustUnit();
	#ifdef _DEBUG
		for(int i = 0; i < iRealNeedThreadCount; ++i)
		{
			th[i].showSearchInfo();
		}
	#endif
	}
	void turnResultAsSearchField()
	{
		globalFileList.clear();
		for(auto& item : globalMatchResult)
		{
			globalFileList.push_back(item);
		}
		globalMatchResult.clear();
	}
	void recordTextSearchResultIntoFile()
	{
		FileWriter fw;
		fw.open(resultFileName);
		writeSearchResultTitle(fw,"text");
		for(auto& item : globalMatchResult)
		{
			std::stringstream ss;
			ss.fill(' ');
			ss.width(50);
			ss << item.getPath() << "        ";
			for(auto& line : item.getMatchedLines())
			{
				ss << line << " ";
			}
			fw.writeLine(ss.str());
		}
		fw.close();
	}
	void recordFileSearchResultIntoFile()
	{
		FileWriter fw;
		fw.open(resultFileName);
		writeSearchResultTitle(fw,"file");
		for(auto& item : globalMatchResult)
		{
			std::stringstream ss;
			ss.fill(' ');
			ss.width(50);
			ss << item.getPath() << "        " << item.getSize();
			fw.writeLine(ss.str());
		}
		fw.close();
	}
	void writeSearchResultTitle(FileWriter& fw,const std::string mode)
	{
		fw.writeLine("                                                RESULT");
		fw.writeLine("===================================================================================================================");
		fw.writeLine("Search date&time: " + mTimer.getCurrentTime());
		fw.writeLine("Search cost time: " + mStrCostTime);
		fw.writeLine("Search      Mode: " + mode);
		if(mode == "file")
			fw.writeLine("                                          FileName        Size(bytes)");
		else if(mode == "text")
			fw.writeLine("                                          FileName        Match Lines");
		else ;
		fw.writeLine("===================================================================================================================");
	}
	void recordTestData(std::string str)
	{
		assert(str.compare("-t") == 0 or str.compare("-f") == 0);
		FileWriter fw;
		fw.appendOpen(testFileName);
		std::stringstream ss;
		ss << "<Dir: " << mTargetDir << ">  ";
		if(str.compare("-t") == 0)
		{
			ss << "<Text: " << mTargetText << ">  ";
		}
		else
		{
			ss << "<File: " << mTargetFile << ">  ";
		}
		ss <<"<Time:"<< mStrCostTime << ">  "<<std::endl;
		fw.writeLine(ss.str());
		fw.close();
	}
private:
	std::string mTargetDir;
	std::string mTargetFile;
	std::string mTargetText;
	GoThroughAllDir	mGtad;
	static const int SEARCH_TEXT_THREAD_COUNT = 4;
	SearchTextThread th[SEARCH_TEXT_THREAD_COUNT];
	Surface mSurface;
	Timer mTimer;
	std::string mStrCostTime;
};
void split(std::string& str,std::list<std::string>& lst)
{
	std::string temp = "";
	for(unsigned int idx = 0; idx < str.size(); ++idx)
	{
		if(str[idx] == ' ' && temp.size() > 0)
		{
			lst.push_back(temp);
			temp = "";
		}
		else
		{
			temp += str[idx];
		}
	}
	if(str[str.size()-1] != ' ')
	{
		lst.push_back(temp);
	}
}
int main(int argc, char* argv[])
{
	theAppName = argv[0];
	if(std::string::npos == theAppName.find(".exe"))
	{
		theAppName += ".exe";
	}
	theAppName = theAppName.substr(theAppName.find_last_of('\\')+1,theAppName.size());
	std::list<std::string> params;
	if(argc == 1)
	{
		std::string cmd;
		std::cout << "Search command: ";
		getline(std::cin, cmd);
		split(cmd,params);
	}
	else
	{
		for(int idx = 0; idx < argc; ++idx)
		{
			params.push_back(std::string(argv[idx]));
		}
	}
	Clgr clgr;
	ParseCommandLine pcl(argc,params);
	pcl.parse();
	clgr.setTargetDir(pcl.getTargetDir());
	if(pcl.isSearchHelp())
	{
		clgr.help();
	}
	else if(pcl.isSearchFile())
	{
		clgr.setTargetFile(pcl.getTargetFile());
		clgr.searchFile();
	}
	else if(pcl.isSearchText())
	{
		if(pcl.isSearchTextFromSpecificFile())
		{
			GoThroughAllDir gtad(pcl.getTargetDir());
			gtad.setFilter(pcl.getTargetFile());
			gtad.start();
			if(globalFileList.size() == 0)
			{
				std::cerr << "Cannot find the file " << pcl.getTargetFile() << std::endl;
				ErrorLog log;
				log.writeError("cannot find the file " + pcl.getTargetFile());
				exit(-1);
			}
		}
		clgr.setTargetText(pcl.getTargetText());
		clgr.searchText();
	}
	else ;
}