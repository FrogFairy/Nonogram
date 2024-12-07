#include "graph_board.h"

void Graph_board::cb_click_button(Graph_lib::Address, Graph_lib::Address addr)
{
    
}

void Graph_board::init(Graph_lib::Point xy, int w, int h, Level& level)
{
    std::vector<int> size = size_to_int(level.size);
    int font_size = 20;
    int button_size = std::min((h - logic_board.max_cols * font_size) / size[0], (w - logic_board.max_rows) / size[1]);
    int x_margin = w - button_size * size[1];
    int y_margin = h - button_size * size[0];

    for (int i = 0; i < size[0]; ++i)
    {
        Graph_lib::Vector_ref<Graph_lib::Text> r_digits;
        for (int j = 0; j < size[1]; ++j)
        {
            auto button = new Graph_lib::Button{Graph_lib::Point{xy.x + x_margin + j * button_size, xy.y + y_margin + i * button_size}, button_size, button_size, "", cb_click_button};
            buttons.push_back(*button);

            if (j < logic_board.row_digits[i].size())
            {
                auto text = new Graph_lib::Text{Graph_lib::Point(0, 0), std::to_string(logic_board.row_digits[i][j])};
                Graph_lib::Point p{(int) (xy.x + x_margin - (logic_board.row_digits[i].size() - j) * font_size - font_size / 4 * text->length()), 
                                            xy.y + y_margin + i * button_size + std::max(button_size - font_size, font_size)};
                text->move(p.x, p.y);
                text->set_font_size(font_size);
                text->set_color(Graph_lib::Color::black);
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
            auto text = new Graph_lib::Text{Graph_lib::Point(0, 0), std::to_string(logic_board.col_digits[i][j])};
            Graph_lib::Point p{xy.x + x_margin + i * button_size + (button_size - font_size / 2 * text->length()) / 2, 
                                (int) (xy.y + y_margin - (logic_board.col_digits[i].size() - j - 1) * font_size - font_size / 2)};
            text->move(p.x, p.y);
            text->set_font_size(font_size);
            text->set_color(Graph_lib::Color::black);
            c_digits.push_back(*text);
        }
        col_digits.push_back(c_digits);
    }
}

void Graph_board::attach(Graph_lib::Window &win)
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