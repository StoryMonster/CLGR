#include "FileBrowser.hpp"
#include "types/FileInfo.hpp"

#ifdef __WINDOWS__
#include <windows.h>
#endif

namespace common{

FileBrowser::FileBrowser(const std::string& dir) : dir{dir}
{
}

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
                        #ifdef __WINDOWS__
                            folders.push(path + "\\" + fileInfo.name);
                        #else
                            folders.push(path + "/" + fileInfo.name);
                        #endif
                    } 
                }
                else
                {
                    if (filter(fileInfo.name))
                    {
                        files.push(types::FileInfo(fileInfo.name, path, fileInfo.size));
                    }
                }
            }while (_findnext(hFile, &fileInfo) == 0);
            _findclose(hFile);
        }
    }
    return files;
}
}
