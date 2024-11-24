#include <Graph_lib/Graph.h>

#include <vector>
#include <fstream>


std::vector<std::vector<double>> const get_grey_pixels(Graph_lib::Image& img)
{
    int w = img.width(), h = img.height();
    Fl_Offscreen buff = fl_create_offscreen(w, h);
    fl_begin_offscreen(buff);
    img.draw();
    std::ofstream out{"pixels.txt"};
    std::vector<std::vector<double>> result(h, std::vector<double> (w));
    out << "[";
    for (int j = 0; j < h; ++j)
    {
        out << "[";
        for (int i = 0; i < w; ++i)
        {
            uchar pixel[3];
            fl_read_image(pixel, i, j, 1, 1, 0);
            out << "[" << (int) pixel[0] << ", " << (int) pixel[1] << ", " << (int) pixel[2] << "]";
            if (i != w - 1) out << ", ";
            double grey_pixel = 0.2125 * pixel[0] + 0.7154 * pixel[1] + 0.0721 * pixel[2];
            result[j][i] = grey_pixel;
        }
        out << "]";
        if (j != h - 1) out << ", ";
    }
    out << "]";
    fl_end_offscreen();
    fl_delete_offscreen(buff);
    return result;
}

std::vector<std::vector<double>> const get_integral_sum(const std::vector<std::vector<double>>& pixels)
{
    int w = pixels[0].size(), h = pixels.size();
    std::vector<std::vector<double>> result(h, std::vector<double> (w));
    for (int i = 0; i < w; ++i)
    {
        int sum = 0;
        for (int j = 0; j < h; ++j)
        {
            // sum += pixels[j][i];
            // if (i == 0)
            //     result[j][i] = sum;
            // else
            //     result[j][i] = pixels[j][i - 1] + sum;

            result[j][i] = pixels[j][i];
            if (i > 0) result[j][i] += result[j][i - 1];
            if (j > 0) result[j][i] += result[j - 1][i];
            if (i * j > 0) result[j][i] -= result[j - 1][i - 1];
        }
    }
    return result;    
}

std::vector<std::vector<std::vector<int>>> const brandley_method(Graph_lib::Image& img)
{
    int w = img.width(), h = img.height();
    std::vector<std::vector<double>> pixels = get_grey_pixels(img);
    std::vector<std::vector<double>> integral_sum = get_integral_sum(pixels);
    int d = w/8, d1 = d / 2, t = 0.15;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    int sum = 0, count = 0;
    std::vector<std::vector<std::vector<int>>> result(h, std::vector<std::vector<int>> (w));
    
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            x1 = std::max(i - d1, 0);
            x2 = std::min(i + d1, w - 1);
            y1 = std::max(j - d1, 0);
            y2 = std::min(j + d1, h - 1);

            count = (x2 - x1) * (y2 - y1);
            sum = integral_sum[y2][x2] - integral_sum[y1][x2] - integral_sum[y2][x1] + integral_sum[y1][x1];
            if ((long)(pixels[j][i] * count) < (long) (sum * (1. - t)))
                result[j][i] = {0, 0, 0};
            else
                result[j][i] = {255, 255, 255};
        }
    }
    return result;
}

double const get_limit(const std::vector<std::vector<double>>& pixels)
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

std::vector<std::vector<std::vector<int>>> const brightness_method(Graph_lib::Image& img)
{
    int w = img.width(), h = img.height();
    std::vector<std::vector<double>> pixels = get_grey_pixels(img);
    std::vector<std::vector<std::vector<int>>> result(h, std::vector<std::vector<int>> (w));
    double t = get_limit(pixels);
    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
        {
            if (pixels[j][i] < t) result[j][i] = {255, 255, 255};
            else result[j][i] = {0, 0, 0};
        }
    }
    return result;
}

int main()
{
    Graph_lib::Image img {Graph_lib::Point{0, 0}, "resources/hamster.jpg"};
    img.resize(30, 30);
    int w = img.width(), h = img.height();

    std::ofstream out {"black_pixels.txt"};
    out << "[";
    std::vector<std::vector<std::vector<int>>> pixels = brightness_method(img);
    for (int j = 0; j < h; ++j)
    {
        out << "[";
        for (int i = 0; i < w; ++i)
        {
            out << "[" << pixels[j][i][0] << ", " << pixels[j][i][1] << ", " << pixels[j][i][2] << "]";
            if (i != w - 1) out << ", ";
        }
        out << "]";
        if (j != h - 1) out << ", ";
    }
    out << "]";
}