#ifndef GRAPH_BOARD.H
#define GRAPH_BOARD.H

#include <Graph_lib/GUI.h>
#include <vector>

#include "buttons.h"

struct Graph_board : Graph_lib::Widget
{
public:
    Graph_board(Graph_lib::Point xy, int w, int h, int rows, int cols)
        : Widget{xy, w, h, "", nullptr}, rows(rows), cols(cols)
    {
        int button_width=w/cols;
        int button_height=h/rows;
        for (int i = 0; i < rows; ++i)
        {
            std::vector<Graph_lib::Button *> row_buttons;
            for (int j = 0; j < cols; ++j)
            {
                auto button = new Graph_lib::Button{Graph_lib::Point{xy.x + j * button_width, xy.y + i * button_height}, button_width, button_height, "", cb_play_button};
                row_buttons.push_back(button);
                selection.push_back(*button); 
            }
            buttons.push_back(row_buttons);
        }
    }

    Graph_lib::Vector_ref<Graph_lib::Button> selection;

    void attach(Graph_lib::Window &win)
    { 
        for (int i = 0; i < selection.size(); ++i)
            win.attach(selection[i]);
        own = &win;
    }

    void show()
    {
        for (int i = 0; i < selection.size(); ++i)
            selection[i].show();
    }

    void hide()
    {
        for (int i = 0; i < selection.size(); ++i)
            selection[i].hide();
    }

    void move(int dx, int dy)
    { 
        for (int i = 0; i < selection.size(); ++i)
            selection[i].move(dx, dy);
    }

    
private:
    static void cb_play_button(Graph_lib::Address, Graph_lib::Address addr);

    int rows;
    int cols;
    int w;
    int h;
    
    std::vector<std::vector<Graph_lib::Button *>> buttons;
    Graph_lib::Window *own = nullptr;                      
};


#endif