#include "Args.hpp"
#include <stdexcept>

namespace args {

Args::Args(int argc, char** argv) {
    exeFile = std::string(argv[0]);
    for (int i = 1; i < argc; ++i) {
        cmdArgs.push_back(std::string(argv[i]));
    }
}

void Args::AddParameter(const std::string& key, const std::string& abbr, const std::vector<std::string>& defaultVal, const std::string& desc) {
    if (params.find(key) != params.end() || abbrs.find(abbr) != abbrs.end()) { return; }
    params.emplace(key, Param{key, abbr, desc, defaultVal, {}, false});
    abbrs.emplace(abbr, key);
}

std::map<std::string, Param> Args::parse() {
    Param param{};
    std::string key{};
    std::string abbr{};
    for (const auto& cmdArg: cmdArgs) {
        if (cmdArg.find("--") == 0) {
            try {
                if (key.size() > 0) { params.at(key) = param; }
                key = cmdArg.substr(2);
                param = params.at(key);
                param.isExist = true;
            } catch (const std::out_of_range& err) {
                throw err;
            }
        } else if (cmdArg.find("-") == 0) {
            try {
                if (key.size() > 0) { params.at(key) = param; }
                abbr = cmdArg.substr(1);
                key = abbrs.at(abbr);
                param = params.at(key);
                param.isExist = true;
            } catch (const std::out_of_range& err) {
                throw err;
            }
        } else {
            param.value.push_back(cmdArg);
        }
    }
    return params;
}
}