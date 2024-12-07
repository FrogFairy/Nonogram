#ifndef GRAPH_BOARD_H
#define GRAPH_BOARD_H

#include <Graph_lib/GUI.h>
#include <Graph_lib/Graph.h>
#include "buttons.h"
#include "database.h"
#include "logic_board.h"

#include <vector>
#include <algorithm>

struct Graph_board : Graph_lib::Widget
{
public:
    Graph_board(Graph_lib::Point xy, int w, int h, Level& level)
        : Widget{xy, w, h, "", nullptr}, logic_board{Logic_board(level)}
    {
        std::vector<int> size = size_to_int(level.size);
        int font_size = 20;
        int button_size = std::min((h - logic_board.max_rows * font_size) / size[0], (w - logic_board.max_cols * font_size) / size[1]);
        int x_margin = (w - button_size * size[1]) / 2;
        int y_margin = (h - button_size * size[0]) / 2;
        std::cout << x_margin << " " << y_margin << std::endl;

        for (int i = 0; i < size[0]; ++i)
        {
            Graph_lib::Vector_ref<Graph_lib::Text> r_digits;
            for (int j = 0; j < size[1]; ++j)
            {
                auto button = new Graph_lib::Button{Graph_lib::Point{xy.x + x_margin + j * button_size, xy.y + y_margin + i * button_size}, button_size, button_size, "", cb_click_button};
                buttons.push_back(*button);

                if (j < logic_board.row_digits[i].size())
                {
                    Graph_lib::Point p{(int) (xy.x + x_margin - (logic_board.row_digits[i].size() - j) * font_size), xy.y + y_margin + i * button_size + button_size / 2};
                    auto text = new Graph_lib::Text{p, std::to_string(logic_board.row_digits[i][j])};
                    text->set_font_size(font_size);
                    r_digits.push_back(*text);
                }
            }
            row_digits.push_back(r_digits);
        }

        for (int i = 0; i < size[1]; ++i)
        {
            Graph_lib::Vector_ref<Graph_lib::Text> c_digits;
            for (int j = 0; j < logic_board.col_digits[i].size(); ++j)
            {
                Graph_lib::Point p{xy.x + x_margin + i * button_size + button_size / 2, (int) (xy.y + y_margin - (logic_board.col_digits[i].size() - j) * font_size)};
                auto text = new Graph_lib::Text{p, std::to_string(logic_board.col_digits[i][j])};
                text->set_font_size(font_size);
                c_digits.push_back(*text);
            }
            col_digits.push_back(c_digits);
        }
    }

    std::string digits_to_string(std::vector<int>& digits, char delimiter)
    {
        std::string res = "";
        for (int i = 0; i < digits.size(); ++i)
        {
            res += std::to_string(digits[i]);
            if (i != digits.size() - 1) res += delimiter;
        }
        return res;
    }

    void attach(Graph_lib::Window &win)
    { 
        for (int i = 0; i < buttons.size(); ++i)
        {
            win.attach(buttons[i]);
            if (i < row_digits.size())
            {
                for (int j = 0; j < row_digits[i].size(); ++j)
                {
                    win.attach(row_digits[i][j]);
                }
            }
            if (i < col_digits.size())
                for (int j = 0; j < col_digits[i].size(); ++j)
                {
                    win.attach(col_digits[i][j]);
                }
        }
        own = &win;
    }

    
private:
    static void cb_click_button(Graph_lib::Address, Graph_lib::Address addr);

    Graph_lib::Vector_ref<Graph_lib::Button> buttons;
    std::vector<Graph_lib::Vector_ref<Graph_lib::Text>> row_digits;
    std::vector<Graph_lib::Vector_ref<Graph_lib::Text>> col_digits;

    Logic_board logic_board;
};


#endif // GRAPH_BOARD_H