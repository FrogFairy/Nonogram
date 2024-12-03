#include <string>
#include <vector>

std::vector<int> size_to_int(const std::string& size)
{
    int w = std::stoi(size.substr(0, size.find("x")));
    int h = std::stoi(size.substr(size.find("x" + 1)));
    return std::vector<int> {w, h};
}