#ifndef CREATE_LEVEL_H
#define CREATE_LEVEL_H

#include <Graph_lib/Graph.h>
#include <vector>

std::vector<std::vector<double>> const get_grey_pixels(const Graph_lib::Image&);
std::vector<std::vector<double>> const resize(std::vector<std::vector<double>>& pixels, int new_w, int new_h);
double get_limit(const std::vector<std::vector<double>>&);
std::vector<std::vector<int>> const brightness_method(std::vector<std::vector<double>>& pixels);
std::vector<std::vector<int>> const create_matrix_level(int w, int h, const std::string& filename);

#endif // CREATE_LEVEL_H