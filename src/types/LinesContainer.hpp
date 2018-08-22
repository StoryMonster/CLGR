#pragma once
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <ostream>
#include <vector>
#include <utility>

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

    std::vector<std::pair<std::uint32_t, std::string>> getLines() const
    {
        return lines;
    }

    void addLine(const std::pair<std::uint32_t, std::string>& lineInfo)
    {
        lines.emplace_back(lineInfo);
    }

    bool containLines() const
    {
        return lines.size() > 0;
    }
    friend std::ostream& operator<<(std::ostream&, const LinesContainer&);
private:
    std::string fileName;
    std::vector<std::pair<std::uint32_t, std::string>> lines;
};

std::ostream& operator<<(std::ostream& os, const LinesContainer& container)
{
    std::stringstream ss{};
    ss << ">>>" << container.getFileName() << "\n";
    for (const auto& lineInfo : container.getLines())
    {
        ss << std::setw(5) << lineInfo.first << ": ";
        ss << lineInfo.second << '\n';
    }
    os << ss.str();
    return os;
}
}