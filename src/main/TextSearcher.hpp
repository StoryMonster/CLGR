#pragma once
#include "src/types/SearchInfo.hpp"
#include "src/common/FileBrowser.hpp"
#include "src/common/utils.hpp"
#include "src/common/Semaphore.hpp"
#include "src/common/FileReader.hpp"
#include <vector>

#ifdef __WINDOWS__
#include <mingw.thread.h>
#include <windows.h>
#else
#include <thread>
#endif

bool isBinaryLine(const std::string& line)
{
    for (const auto ch : line)
    {
        if(ch == 0x00 || ch == 0x01 || ch == 0x02 || ch == 0x03 || ch == 0x04 ||
           ch == 0x05 || ch == 0x06 || ch == 0x07)
        return true;
    }
    return false;
}

bool isMatchedFileType(const std::string& fileName, const std::string& type)
{
    const auto typeLength = type.size();
    const auto fileNameLength = fileName.size();
    if (fileNameLength <= typeLength)
    {
        return false;
    }
    return fileName.substr(fileNameLength-typeLength) == type;
}

bool isValidSearchingFile(const std::string& fileName)
{
    if (isMatchedFileType(fileName, ".doc") || isMatchedFileType(fileName, ".exe") ||
        isMatchedFileType(fileName, ".dll") || isMatchedFileType(fileName, ".o") ||
        isMatchedFileType(fileName, ".so") || isMatchedFileType(fileName, ".Mp4") ||
        isMatchedFileType(fileName, ".mp4") || isMatchedFileType(fileName, ".pdf") ||
        isMatchedFileType(fileName, ".ppt") || isMatchedFileType(fileName, ".avi") ||
        isMatchedFileType(fileName, ".mp3") || isMatchedFileType(fileName, ".a"))
    {
        return false;
    }
    return true;
}

void searchTextInFiles(const std::string& text, std::queue<types::FileInfo>& files,
                       common::Semaphore& sem)
{
    while (files.size())
    {
        sem.wait();
        auto file = files.front();
        files.pop();
        sem.release();
        common::FileReader reader(file.getCompletePath());
        std::uint32_t lineCounter = 0;
        bool findoutText = false;
        while (!reader.isReadToEnd())
        {
            std::string line = reader.readLine();
            if (isBinaryLine(line)) { break; }
            ++lineCounter;
            if (text.size() <= line.size() && line.find(text) != std::string::npos)
            {
                if (!findoutText)
                {
                    findoutText = true;
                    LOG_INFO << "\n>>>" << file.getCompletePath() << '\n';
                }
                LOG_INFO << std::setw(5) << lineCounter << ": ";
                LOG_INFO << line << '\n';
            }
        }
    }
}

class TextSearcher
{
public:
    TextSearcher(const std::string& text, const types::SearchField& field)
    : text{text}, searchField(field), fileBrowser(searchField.dir)
    {}

    void search()
    {
        auto searchFilter = [&](const std::string& fileName)
        {
            if (!isValidSearchingFile(fileName))
            {
                return false;
            }
            for (const auto& item : searchField.files)
            {
                if (fileName.size() < item.size() || fileName.find(item) == std::string::npos)
                {
                    return false;
                }
            }
            return true;
        };
        auto files = fileBrowser.extractFiles(searchFilter);
        const auto parallelThreadNum = common::utils::getNecessaryThreadNumbers(files.size());

        #ifdef __WINDOWS__
            auto sem = common::WindowsSemaphore("TextSearcher", 1, 1);
        #else
            sem_t sem_t_;
            auto sem = common::LinuxSemaphore(sem_t_);
        #endif

        std::vector<std::thread> threads;
        for (auto i = 0; i < parallelThreadNum; ++i)
        {
            threads.emplace_back(std::thread(searchTextInFiles, text, std::ref(files), std::ref(sem)));
        }
        for (auto i = 0; i < parallelThreadNum; ++i)
        {
            threads[i].join();
        }
    }

private:
    const std::string text;
    types::SearchField searchField;
    common::FileBrowser fileBrowser;
};
