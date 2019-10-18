#pragma once
#include <vector>
#include <string>
#include <map>

namespace args {

struct Param {
    std::string key{};
    std::string abbr{};
    std::string desc{};
    std::vector<std::string> defaultVal{};
    std::vector<std::string> value{};
    bool isExist{false};
};

class Args {
public:
    Args(int argc, char** argv);
    void AddParameter(const std::string& key, const std::string& abbr, const std::vector<std::string>& defaultVal, const std::string& desc);
    std::map<std::string, Param> parse();

private:
    std::map<std::string, Param> params;        // <key, param>
    std::map<std::string, std::string> abbrs;   // <abbr, key>
    std::vector<std::string> cmdArgs{};
    std::string exeFile{};
};
}