#include "FileBrowser.hpp"
#include "src/types/FileInfo.hpp"
#include <cstring>
#include <iostream>

#ifdef __WINDOWS__
#include <io.h>
#else
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#endif

namespace common{

FileBrowser::FileBrowser(const std::string& dir) : dir{dir}
{
}

#ifdef __WINDOWS__
std::queue<types::FileInfo> FileBrowser::extractFiles(const Filter filter)
{
    std::queue<types::FileInfo> files;
    std::queue<std::string> folders;
    struct _finddata_t fileInfo;
    folders.push(dir);
    while(folders.size())
    {
        std::string path = folders.front();
        folders.pop();
        long hFile = _findfirst((path + "/*").c_str(), &fileInfo);
        if (hFile != -1)
        {
            do
            {
                if (fileInfo.attrib & _A_SUBDIR)
                {
                    if (strcmp(fileInfo.name, ".") !=0 && strcmp(fileInfo.name, "..") != 0)
                    {
                        folders.push(path + "\\" + fileInfo.name);
                    }
                }
                else if (filter(fileInfo.name))
                {
                    files.push(types::FileInfo(fileInfo.name, path));
                }
            }while (_findnext(hFile, &fileInfo) == 0);
            _findclose(hFile);
        }
    }
    return files;
}

void FileBrowser::showFiles(const Filter filter)
{
    std::queue<std::string> folders;
    struct _finddata_t fileInfo;
    folders.push(dir);
    while(folders.size())
    {
        std::string path = folders.front();
        folders.pop();
        long hFile = _findfirst((path + "/*").c_str(), &fileInfo);
        if (hFile != -1)
        {
            do
            {
                if (fileInfo.attrib & _A_SUBDIR)
                {
                    if (strcmp(fileInfo.name, ".") !=0 && strcmp(fileInfo.name, "..") != 0)
                    {
                        folders.push(path + "\\" + fileInfo.name);
                    }
                }
                else if (filter(fileInfo.name))
                {
                    std::cout << types::FileInfo(fileInfo.name, path) << std::endl;
                }
            }while (_findnext(hFile, &fileInfo) == 0);
            _findclose(hFile);
        }
    }
}

#else
std::queue<types::FileInfo> FileBrowser::extractFiles(const Filter filter)
{
    std::queue<std::string> folders;
    std::queue<types::FileInfo> files;
    folders.push(dir);
    while (folders.size())
    {
        std::string folder = folders.front();
        folders.pop();
        DIR* pFolder = opendir(folder.c_str());
        while (true)
        {
            struct dirent* file = readdir(pFolder);
            if (file == NULL) { break; }
            if (strcmp(file->d_name, "..") == 0 || strcmp(file->d_name, ".") == 0) { continue; }
            if (file->d_type == DT_DIR)
            {
                folders.push(folder + "/" + file->d_name);
            }
            else if (filter(file->d_name))
            {
                files.push(types::FileInfo(file->d_name, folder));
            }
        }
        closedir(pFolder);
    }
    return files;
}

void FileBrowser::showFiles(const Filter filter)
{
    std::queue<std::string> folders;
    folders.push(dir);
    while (folders.size())
    {
        std::string folder = folders.front();
        folders.pop();
        DIR* pFolder = opendir(folder.c_str());
        while (true)
        {
            struct dirent* file = readdir(pFolder);
            if (file == NULL) { break; }
            if (strcmp(file->d_name, "..") == 0 || strcmp(file->d_name, ".") == 0) { continue; }
            if (file->d_type == DT_DIR)
            {
                folders.push(folder + "/" + file->d_name);
            }
            else if (filter(file->d_name))
            {
                std::cout << types::FileInfo(file->d_name, folder) << std::endl;
            }
        }
        closedir(pFolder);
    }
}
#endif
}
