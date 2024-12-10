#include "create_level.h"

#include <string>
#include <iostream>


std::vector<std::vector<double>> const get_grey_pixels(Graph_lib::Image& img)
{
    int w = img.width(), h = img.height();
    Fl_Offscreen buff = fl_create_offscreen(w, h);
    fl_begin_offscreen(buff);
    img.draw();
    std::vector<std::vector<double>> result(h, std::vector<double> (w));
    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
        {
            uchar pixel[3];
            fl_read_image(pixel, i, j, 1, 1, 0);
            double grey_pixel = 0.2125 * pixel[0] + 0.7154 * pixel[1] + 0.0721 * pixel[2];
            result[j][i] = grey_pixel;
        }
    }
    fl_end_offscreen();
    fl_delete_offscreen(buff);
    return result;
}

double const get_limit(std::vector<std::vector<double>>& pixels)
{
    int w = pixels[0].size(), h = pixels.size();
    int x1, x2, y1, y2;
    double g_m, g_n;
    double sum_f_g, sum_g;
    std::vector<std::vector<double>> gradient_brightness(h, std::vector<double> (w));
    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
        {
            g_m = (j + 1 < h ? pixels[j + 1][i] : 0) - (j - 1 >= 0 ? pixels[j - 1][i] : 0);
            g_n = (i + 1 < w ? pixels[j][i + 1] : 0) - (i - 1 >= 0 ? pixels[j][i - 1] : 0);
            gradient_brightness[j][i] = std::max(std::abs(g_m), std::abs(g_n));
            sum_f_g += pixels[j][i] * gradient_brightness[j][i];
            sum_g += gradient_brightness[j][i];
        }
    }
    return sum_f_g / sum_g;
}

std::vector<std::vector<int>> const brightness_method(Graph_lib::Image& img)
{
    int w = img.width(), h = img.height();
    std::vector<std::vector<double>> pixels = get_grey_pixels(img);
    std::vector<std::vector<int>> result(h, std::vector<int> (w));
    double t = get_limit(pixels);
    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
        {
            if (pixels[j][i] < t) result[j][i] = 1; // white pixel, cross
            else result[j][i] = 0; // black pixel, painted
        }
    }
    return result;
}

std::vector<std::vector<int>> const create_matrix_level(int w, int h, const std::string& filename)
{
    Graph_lib::Image img {Graph_lib::Point{0, 0}, filename};
    img.resize(w, h);
    return brightness_method(img);
}