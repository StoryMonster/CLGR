#pragma once
#include "types/SearchInfo.hpp"
#include "common/FileBrowser.hpp"
#include "common/utils.hpp"
#include "common/Logger.hpp"
#include "common/Semaphore.hpp"
#include "common/FileReader.hpp"
#include <iostream>
#include <vector>

#ifdef __WINDOWS__
#include <mingw.mutex.h>
#include <mingw.thread.h>
#else
#include <thread>
#endif

void searchTextInFiles(const std::string& text, std::queue<types::FileInfo>& files, common::Semaphore& sem)
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
            ++lineCounter;
            if (text.size() <= line.size() && line.find(text) != std::string::npos)
            {
                if (!findoutText)
                {
                    findoutText = true;
                    LOG_INFO << "\n>>>" << file.getCompletePath() << '\n';
                }
                LOG_INFO << "  " << lineCounter << " : " << line << '\n';
                //TODO: consider whether there is a risk while all threads use LOG_INFO
            }
        }
    }
}

class TextSearcher
{
public:
    TextSearcher(const std::string& text, const types::SearchField& field)
    : text{text}, searchField(field), fileBrowser(searchField.dir), sem("TextSearcher", 1, 1)
    {}

    void search()
    {
        auto searchFilter = [&](const std::string& fileName)
        {
            if (searchField.files.size() == 0) {return true;}
            if (fileName.find(".doc") != std::string::npos || fileName.find(".excel") != std::string::npos ||
                fileName.find(".exe") != std::string::npos || fileName.find(".out") != std::string::npos ||
                fileName.find(".docx") != std::string::npos || fileName.find(".bin") != std::string::npos ||
                fileName.find(".dll") != std::string::npos || fileName.find(".so") != std::string::npos ||
                fileName.find(".pdf") != std::string::npos || fileName.find(".ppt") != std::string::npos ||
                fileName.find(".mp4") != std::string::npos || fileName.find(".avi") != std::string::npos ||
                fileName.find(".Mp4"))
            {
                return false;
            }
            for (const auto& item : searchField.files)
            {
                if (fileName.size() >= item.size() && fileName.find(item) != std::string::npos)
                {
                    return true;
                }
            }
            return false;
        };
        auto files = fileBrowser.extractFiles(searchFilter);
        const auto parallelThreadNum = common::utils::getNecessaryThreadNumbers(files.size());
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
    common::Semaphore sem;
};
