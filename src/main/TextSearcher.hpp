#pragma once
#include "src/types/SearchInfo.hpp"
#include "src/types/LinesContainer.hpp"
#include "src/common/FileBrowser.hpp"
#include "src/common/utils.hpp"
#include "src/common/Semaphore.hpp"
#include "src/common/FileReader.hpp"
#include "src/exceptions/SemaphoreError.hpp"
#include "src/common/SearchFilterFactory.hpp"
#include <vector>
#include <iostream>
#include <sstream>

#ifdef __WINDOWS__
#include <mingw.thread.h>
#include <windows.h>
#else
#include <thread>
#endif

bool isMatchedFileType(const std::string& fileName, const std::vector<std::string> types)
{
    const auto fileNameLength = fileName.size();
    for (const auto& type : types)
    {
        const auto typeLength = type.size();
        if (fileNameLength <= typeLength) { continue; }
        if (common::utils::toLower(fileName.substr(fileNameLength-typeLength)) == type)
        {
            return true;
        }
    }
    return false;
}

bool isValidSearchingFile(const std::string& fileName)
{
    return not isMatchedFileType(fileName, {
        // libs
        ".dll", ".so", ".a",
        // binary files
        ".exe", ".out", ".bin", ".apk", ".msi",
        // microsoft office
        ".doc", ".pptx", ".ppt", ".xlsm", ".pdf", ".xlsx", ".docx",
        // video
        ".mp4", ".avi", ".rmvb",
        // audio
        ".mp3", ".wmv",
        // others
        ".o", ".zip", ".tar"
    });
}

bool isTheLineMatched(const std::string& text, const std::string& line, bool matchWholeWord)
{
    return matchWholeWord ? common::utils::isWordWholeMatched(text, line) : (line.find(text) != std::string::npos);
}

void searchTextInFileAndShowResult(const types::FileInfo& file, const std::string& text, const common::CaseSensitiveFilter& caseSensitiveFilter,
                                   const common::WholeMatchFilter& wholeMatchFilter) try
{
    const auto fileName = file.getCompletePath();
    common::FileReader reader(fileName);
    types::LinesContainer container(fileName);
    for (std::uint32_t lineCounter = 1; !reader.isReadToEnd(); ++lineCounter)
    {
        const auto line = reader.readLine();
        if (common::utils::isBinaryLine(line)) { break; }
        if (not common::SearchFilterFactory::isBasicMatched(text, line)) { continue; }
        if (wholeMatchFilter(text, line) && caseSensitiveFilter(text, line))
        {
            container.addLine({lineCounter, line});
        }
    }
    if (container.containLines())
    {
        std::cout << container << std::endl;
    }
}
catch (const exceptions::FileError& err)
{
    std::cout << err.what() << std::endl;
}

void searchTextInFiles(const std::string& text, std::deque<types::FileInfo>& files,
                       const common::CaseSensitiveFilter& caseSensitiveFilter,
                       const common::WholeMatchFilter& wholeMatchFilter,
                       common::Semaphore& sem)
{
    static std::uint32_t count = 0;
    while (files.size() > count)
    {
        try { sem.wait(); }
        catch (const exceptions::SemaphoreWaitError&) { sem.release(); continue; }
        //it's not thread safe in linux scenario, but safe in windows scenario. use files.at() is a temporary solution.
        //const auto file = files.front();
        //files.pop_front();
        const auto file = files.at(count++);
        sem.release();
        searchTextInFileAndShowResult(file, text, caseSensitiveFilter, wholeMatchFilter);
    }
}

class TextSearcher
{
public:
    TextSearcher(const std::string& text, const types::SearchField& field, const types::SearchOptions& options)
    : text{text}, searchField(field), options(options), fileBrowser(searchField.dir)
    , searchFilterFactory(options), caseSensitiveFilter{searchFilterFactory.createCaseSensitiveFilter()}
    , wholeMatchFilter{searchFilterFactory.createWholeMatchFilter()}
    {}

    void search()
    {
        auto searchFilter = [&](const std::string& fileName)
        {
            if (searchField.files.size() == 0) { return true; }
            if (!isValidSearchingFile(fileName)) { return false; }
            for (const auto& item : searchField.files)
            {
                if (not common::SearchFilterFactory::isBasicMatched(item, fileName)) { continue; }
                if (wholeMatchFilter(item, fileName) && caseSensitiveFilter(item, fileName))
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

        std::vector<std::thread> threads{};
        threads.reserve(parallelThreadNum);
        for (std::uint8_t i = 0; i < parallelThreadNum; ++i)
        {
            threads.emplace_back(std::thread(searchTextInFiles, text, std::ref(files),
                                             ref(caseSensitiveFilter), ref(wholeMatchFilter), std::ref(sem)));
        }
        for (std::uint8_t i = 0; i < parallelThreadNum; ++i)
        {
            threads[i].join();
        }
    }

private:
    const std::string text;
    types::SearchField searchField;
    types::SearchOptions options;
    common::FileBrowser fileBrowser;
    common::SearchFilterFactory searchFilterFactory;
    common::CaseSensitiveFilter caseSensitiveFilter;
    common::WholeMatchFilter wholeMatchFilter;
};
