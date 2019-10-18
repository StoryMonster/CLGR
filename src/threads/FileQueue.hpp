#pragma once
#include <queue>
#include <mutex>
#include <string>

namespace threads {

class FileQueue {
public:
    FileQueue();
    void push(const std::string& file);
    std::string pop();
    inline bool empty() {
        mt.lock();
        bool res = files.empty();
        mt.unlock();
        return res;
    }

private:
    std::queue<std::string> files{};
    std::mutex mt;
};

}