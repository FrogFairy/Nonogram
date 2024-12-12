#ifndef CREATE_LEVEL_H
#define CREATE_LEVEL_H

#include <vector>
#include <string>

struct Size;

std::vector<std::vector<int>> const create_matrix_level(Size size, const std::string& filename);

#endif // CREATE_LEVEL_H