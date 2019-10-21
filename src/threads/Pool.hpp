#pragma once
#include <vector>
#include <thread>
#include <functional>
#include <atomic>
#include "FileQueue.hpp"

namespace threads {

class FileQueue;

class Pool {
public:
    Pool(const std::function<void(const std::string& filename)>& task);
    void start();
    void destroy();
    void addFile(const std::string& filename);
    bool hasTasks();

private:
    std::vector<std::thread> ths{};
    std::function<void(const std::string& filename)> task{};
    FileQueue files{};
    std::atomic<bool> isWorking{false};
};
}