#include "FileBrowser.hpp"
#include "src/types/FileInfo.hpp"
#include <cstring>

#ifdef __WINDOWS__
#include <io.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
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
                    files.push(types::FileInfo(fileInfo.name, path, fileInfo.size));
                }
            }while (_findnext(hFile, &fileInfo) == 0);
            _findclose(hFile);
        }
    }
    return files;
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
                struct stat buf;
                std::string path = folder + "/" + file->d_name;
                lstat(path.c_str(), &buf);
                const auto size = buf.st_size;
                files.push(types::FileInfo(file->d_name, folder, size));
            }
        }
        closedir(pFolder);
    }
    return files;
}
#endif
}
