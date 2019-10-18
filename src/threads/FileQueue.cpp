#include "FileQueue.hpp"

namespace threads {

FileQueue::FileQueue() {}

void FileQueue::push(const std::string& filename) {
    mt.lock();
    files.push(filename);
    mt.unlock();
}

std::string FileQueue::pop() {
    std::string filename = "";
    mt.lock();
    if (!files.empty()) {
        filename = files.front();
        files.pop();
    }
    mt.unlock();
    return filename;
}
}