#pragma once
#include "src/types/SearchInfo.hpp"
#include "src/common/FileBrowser.hpp"
#include "src/common/utils.hpp"
#include "src/common/Semaphore.hpp"
#include "src/common/FileReader.hpp"
#include "src/exceptions/SemaphoreError.hpp"
#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>

#ifdef __WINDOWS__
#include <mingw.thread.h>
#include <windows.h>
#else
#include <thread>
#endif

bool isMatchedFileType(const std::string& fileName, const std::string& type)
{
    const auto typeLength = type.size();
    const auto fileNameLength = fileName.size();
    if (fileNameLength <= typeLength)
    {
        return false;
    }
    return common::utils::toLower(fileName.substr(fileNameLength-typeLength)) == type;
}

bool isValidSearchingFile(const std::string& fileName)
{
    return !(
        // libs
        isMatchedFileType(fileName, ".dll") || isMatchedFileType(fileName, ".so") || isMatchedFileType(fileName, ".a") ||
        // binary files
        isMatchedFileType(fileName, ".exe") || isMatchedFileType(fileName, ".out") || isMatchedFileType(fileName, ".bin") ||
        isMatchedFileType(fileName, ".apk") ||
        // microsoft office
        isMatchedFileType(fileName, ".doc") || isMatchedFileType(fileName, ".pptx") || isMatchedFileType(fileName, ".ppt") ||
        isMatchedFileType(fileName, ".pdf") || isMatchedFileType(fileName, ".xlsx") || isMatchedFileType(fileName, ".xlsm") ||
        isMatchedFileType(fileName, ".docx") ||
        // vedio
        isMatchedFileType(fileName, ".mp4") || isMatchedFileType(fileName, ".avi") || isMatchedFileType(fileName, ".rmvb") ||
        // music
        isMatchedFileType(fileName, ".mp3") || isMatchedFileType(fileName, ".wmv") ||
        // others
        isMatchedFileType(fileName, ".o") || isMatchedFileType(fileName, ".zip") || isMatchedFileType(fileName, ".tar")
        );
}

void addLineIntoStream(std::stringstream& stream, const std::string& line, std::uint32_t lineCounter)
{
    stream << std::setw(5) << lineCounter << ": ";
    stream << line << '\n';
}

void addFileNameIntoStream(std::stringstream& stream, const std::string& fileName)
{
    stream << ">>>" << fileName << '\n';
}

bool isTheLineMatched(const std::string& text, const std::string& line, bool matchWholeWord)
{
    return matchWholeWord ? common::utils::isWordWholeMatched(text, line) : (line.find(text) != std::string::npos);
}

void searchTextInFileAndShowResult(const types::FileInfo& file, const std::string& text, const types::SearchOptions& options)
{
    common::FileReader reader(file.getCompletePath());
    bool findoutText = false;
    std::stringstream resultToPrint{};
    const auto _text = options.caseSensitive ? text : common::utils::toLower(text);
    for (std::uint32_t lineCounter = 1; !reader.isReadToEnd(); ++lineCounter)
    {
        const auto line = reader.readLine();
        if (common::utils::isBinaryLine(line)) { break; }
        const auto _line = options.caseSensitive ? line : common::utils::toLower(line);
        if (isTheLineMatched(_text, _line, options.matchWholeWord))
        {
            if (!findoutText)
            {
                findoutText = true;
                addFileNameIntoStream(resultToPrint, file.getCompletePath());
                addLineIntoStream(resultToPrint, line, lineCounter);
            }
            else
            {
                addLineIntoStream(resultToPrint, line, lineCounter);
            }
        }
    }
    if (findoutText) { std::cout << resultToPrint.str() << std::endl; }
}

void searchTextInFiles(const std::string& text, const types::SearchOptions& options,
                       std::queue<types::FileInfo>& files, common::Semaphore& sem)
{
    while (files.size() != 0)
    {
        try { sem.wait(); }
        catch (const exceptions::SemaphoreWaitError&) { continue; }
        const auto file = files.front();
        files.pop();
        sem.release();
        searchTextInFileAndShowResult(file, text, options);
    }
}

class TextSearcher
{
public:
    TextSearcher(const std::string& text, const types::SearchField& field, const types::SearchOptions& options)
    : text{text}, searchField(field), options(options), fileBrowser(searchField.dir)
    {}

    void search()
    {
        auto searchFilter = [&](const std::string& fileName)
        {
            if (searchField.files.size() == 0) { return true; }
            if (!isValidSearchingFile(fileName)) { return false; }
            const auto _fileName = common::utils::toLower(fileName);
            for (const auto& item : searchField.files)
            {
                const auto _item = common::utils::toLower(item);
                if (_fileName.find(_item) != std::string::npos)
                {
                    return true;
                }
            }
            return false;
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
            threads.emplace_back(std::thread(searchTextInFiles, text, options, std::ref(files), std::ref(sem)));
        }
        for (auto i = 0; i < parallelThreadNum; ++i)
        {
            threads[i].join();
        }
    }

private:
    const std::string text;
    types::SearchField searchField;
    types::SearchOptions options;
    common::FileBrowser fileBrowser;
};
