#pragma once
#include <cstdint>
#include <stringstream>

namespace types
{
class LinesContainer
{
public:
    LinesContainer(const std::string& fileName) : fileName{fileName}, lines{}
    {
    }

    std::string getFileName() const
    {
        return fileName;
    }

    std::string getLines() const
    {
        return lines;
    }
private:
    std::string fileName;
    std::vector<std::pair<std::uint32_t, std::string>> lines;
};

friend ostream& operator<<(ostream& os, const LinesContainer& container)
{
    std::stringstream ss{};
    ss << ">>>" << container.getFileName() << ":\n";
    for (const auto& lineInfo : container.getLines())
    {
        
    }
    os << ">>>"
}
}