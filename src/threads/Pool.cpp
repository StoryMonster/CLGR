#include "Pool.hpp"
#include <iostream>

namespace threads {

void run(FileQueue& files, std::function<void(const std::string& filename)> handler, std::atomic<bool>& isWorking) {
    while (isWorking) {
        std::string filename = files.pop();
        if (filename.size() > 0) {
            handler(filename);
        }
    }
}

Pool::Pool(const std::function<void(const std::string& filename)>& task): task{task} {
    ths.resize(8);
}

void Pool::start() {
    isWorking = true;
    for (auto& th : ths) {
        th = std::thread(run, std::ref(files), task, std::ref(isWorking));
    }
}

void Pool::destroy() {
    isWorking = false;
    for (auto& th : ths) {
        th.join();
    }
}

void Pool::addFile(const std::string& filename) {
    files.push(filename);
}
}