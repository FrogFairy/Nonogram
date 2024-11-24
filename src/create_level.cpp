#include <Graph_lib/Graph.h>

#include <vector>
#include <fstream>


std::vector<std::vector<int>> get_pixels(Graph_lib::Image& img)
{
    int w = img.width(), h = img.height();
    Fl_Offscreen buff = fl_create_offscreen(w, h);
    fl_begin_offscreen(buff);
    img.draw();
    std::ofstream out{"pixels.txt"};
    std::vector<std::vector<int>> result(h, std::vector<int> (w));
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
            int grey_pixel = 0.2125 * pixel[0] + 0.7154 * pixel[1] + 0.0721 * pixel[2];
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

std::vector<std::vector<int>> get_integral_sum(std::vector<std::vector<int>> pixels)
{
    int w = pixels[0].size(), h = pixels.size();
    std::vector<std::vector<int>> result(h, std::vector<int> (w));
    for (int i = 0; i < w; ++i)
    {
        int sum = 0;
        for (int j = 0; j < h; ++j)
        {
            sum += pixels[j][i];
            if (i == 0)
                result[j][i] = sum;
            else
                result[j][i] = pixels[j][i - 1] + sum;
        }
    }
    return result;    
}

std::vector<std::vector<std::vector<int>>> convert_to_black(Graph_lib::Image& img)
{
    int w = img.width(), h = img.height();
    std::vector<std::vector<int>> pixels = get_pixels(img);
    std::vector<std::vector<int>> integral_sum = get_integral_sum(pixels);
    int d = w/8, d1 = d / 2, t = 0.15;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    int sum = 0, count = 0;
    std::vector<std::vector<std::vector<int>>> result(h, std::vector<std::vector<int>> (w));
    
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            x1 = i - d1;
            x2 = i + d1;
            y1 = j - d1;
            y2 = j + d1;

            if (x1 < 0) x1 = 0;
            if (x2 >= w) x2 = w - 1;
            if (y1 < 0) y1 = 0;
            if (y2 >= h) y2 = h - 1;

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

int main()
{
    Graph_lib::Image img {Graph_lib::Point{0, 0}, "resources/heart.png"};
    // img.resize(30, 30);
    int w = img.width(), h = img.height();

    std::ofstream out {"black_pixels.txt"};
    out << "[";
    std::vector<std::vector<std::vector<int>>> pixels = convert_to_black(img);
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