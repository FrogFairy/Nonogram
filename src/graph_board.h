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
        init(xy, w, h, level);
    }

    void init(Graph_lib::Point xy, int w, int h, Level& level);
    void attach(Graph_lib::Window &win);
    
private:
    static void cb_click_button(Graph_lib::Address, Graph_lib::Address addr);
    void click_button();

    Graph_lib::Vector_ref<Graph_lib::Button> buttons;
    std::vector<Graph_lib::Vector_ref<Graph_lib::Text>> row_digits;
    std::vector<Graph_lib::Vector_ref<Graph_lib::Text>> col_digits;

    Logic_board logic_board;
};


#endif // GRAPH_BOARD_H