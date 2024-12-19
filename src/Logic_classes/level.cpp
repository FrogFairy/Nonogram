#include "level.h"
#include <Graph_lib/Graph.h>
#include "constants.h"

#include <string>
#include <iostream>
#include <fstream>

std::string to_string(Size size)
{
    return std::to_string(size.width) + "x" + std::to_string(size.height);
}

Size size_to_int(const std::string& size)
{
    unsigned int w = std::stoi(size.substr(0, size.find("x")));
    unsigned int h = std::stoi(size.substr(size.find("x") + 1));
    return Size{w, h};
}

std::vector<std::vector<double>> get_grey_pixels(Graph_lib::Image& img)
{
    int w = img.width(), h = img.height();

    Fl_Offscreen buff = fl_create_offscreen(w, h);
    fl_begin_offscreen(buff);
    img.draw();

    uchar pixels[w * h * 3];
    fl_read_image(pixels, 0, 0, w, h, 0);

    fl_end_offscreen();
    fl_delete_offscreen(buff);

    std::vector<std::vector<double>> res (h, std::vector<double> (w));

    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            double grey_pixel = r_koeff * pixels[i * w * 3 + j * 3] + g_koeff * pixels[i * w * 3 + j * 3 + 1] + b_koeff * pixels[i * w * 3 + j * 3 + 2];
            res[i][j] = grey_pixel;
        }
    }
    
    return res;
}

double get_threshold(std::vector<std::vector<double>>& pixels)
{
    int w = pixels[0].size(), h = pixels.size();
    double sum_f_g = 0, sum_g = 0;

    std::vector<std::vector<double>> gradient_brightness(h, std::vector<double> (w));
    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
        {
            double g_m = (j + 1 < h ? pixels[j + 1][i] : 0) - (j - 1 >= 0 ? pixels[j - 1][i] : 0);
            double g_n = (i + 1 < w ? pixels[j][i + 1] : 0) - (i - 1 >= 0 ? pixels[j][i - 1] : 0);
            gradient_brightness[j][i] = std::max(std::abs(g_m), std::abs(g_n));
            sum_f_g += pixels[j][i] * gradient_brightness[j][i];
            sum_g += gradient_brightness[j][i];
        }
    }

    return sum_f_g / sum_g;
}

std::vector<std::vector<double>> resize(const std::vector<std::vector<double>>& pixels, Size size)
{
    int w = pixels[0].size(), h = pixels.size();
    int new_w = size.width, new_h = size.height;
    double percent_w = (double) new_w / w, percent_h = (double) new_h / h;

    std::vector<std::vector<double>> result(new_h, std::vector<double> (new_w));
    std::vector<std::vector<int>> count_colors (new_h, std::vector<int> (new_w));

    for (int i = 0; i < h; ++i)
    {
        int y = i * percent_h;
        if (y >= new_h) y = new_h - 1;

        for (int j = 0; j < w; ++j)
        {
            int x = j * percent_w;
            if (x >= new_w) x = new_w - 1;

            count_colors[y][x]++;
            double prev = result[y][x];
            double cur_count = count_colors[y][x];
            result[y][x] = (prev * (cur_count - 1) + pixels[i][j]) / cur_count;
        }
    }

    return result;
}

std::vector<std::vector<Level::Needful>> brightness_method(std::vector<std::vector<double>>& pixels)
{
    int w = pixels[0].size(), h = pixels.size();
    std::vector<std::vector<Level::Needful>> result(h, std::vector<Level::Needful> (w));
    double t = get_threshold(pixels);
    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
        {
            if (pixels[j][i] < t) result[j][i] = Level::Needful::FILLED_VAL; // black pixel, painted
            else result[j][i] = Level::Needful::CROSS_VAL; // white pixel, cross
        }
    }

    return result;
}

std::vector<std::vector<Level::Needful>> Level::create_matrix_level(Size size, const std::string& filename) const
{
    Graph_lib::Image img {Graph_lib::Point{0, 0}, filename};
    auto pixels = get_grey_pixels(img);
    auto pixels1 = resize(pixels, size);
    
    return brightness_method(pixels1);
}