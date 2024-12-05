#ifndef CREATE_LEVEL.H
#define CREATE_LEVEL .H

#include <Graph_lib/Graph.h>

#include <vector>

std::vector<std::vector<double>> const get_grey_pixels(Graph_lib::Image &);
double const get_limit(const std::vector<std::vector<double>> &);
std::vector<std::vector<int>> const brightness_method(Graph_lib::Image &);
std::vector<std::vector<int>> const create_matrix_level(int w, int h, const std::string &filename);

#endif // CREATE_LEVEL.H