#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <windows.h>
#include <iostream>
#include <list>
#include <map>

extern std::list<FileInfo> 		globalFileList;
extern std::list<FileInfo> 	    globalMatchResult;
extern std::string					theAppName;

class Surface
{
public:
	Surface() {}
	virtual ~Surface() {}
	void showResultList()
	{
		for(auto& item : globalMatchResult)
		{
			std::stringstream ss;
			ss.fill(' ');
			ss.width(50);
			ss << item.getPath();
			for(auto& line : item.getMatchedLines())
			{
				ss <<" "<<line;
			}
			std::cout << ss.str() << std::endl;
		}
	}
	void clearScreen()
	{
		system("cls");
	}
	bool noticeNextSearch()
	{
		std::cout << std::endl;
		std::cout << std::endl;
		while(true)
		{
			char choice;
			std::cout << "Continue search from the result list?(y/n)   ";
			std::cin >> choice;
			switch(choice)
			{
				case 'y':
				case 'Y': return true;
				case 'n':
				case 'N': return false;
				default: break;
			}
			std::cout << std::endl;
		}
	}
	void inputNewKeyword(std::string& option, std::string& key)
	{
		while(true)
		{
			std::cout << "Input keyword(input '-h' to get help):";
			std::cin >> option;
			if(option == "-h" || option == "-H")
			{
				break;
			}
			std::cin >> key;
			if((option == "-f" || option == "-F" || option == "-t" || option == "-T") && key.size() > 0)
			{
				break;
			}
		}
	}
	void showHelpGuide()
	{
		std::cout << "-d        set search text/file under this dir" 	<<std::endl;
		std::cout << "-t        set search text in specific files under specific dir" 	<<std::endl;
		std::cout << "-f        set search file under specific dir" 	<<std::endl;
		std::cout << "-h        help" 	<<std::endl;
	}
	
private:
};
#endif