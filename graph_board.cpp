#include "graph_board.h"
#include <Graph_lib/Graph.h>

// Graph_board::Graph_board(Graph_lib::Point xy, int w, int h, int rows, int cols)
//     : Graph_lib::Widget(xy, w, h, "Graph Board", nullptr), rows(rows), cols(cols)
// {
//     Graph_lib::Widget board(xy, w, h, "Graph Board");
//     std::vector<std::vector<Graph_lib::Button>> buttons;
//     std::vector<Graph_lib::Button> buttons;
//     for (int i = 0; i < rows; ++i)
//     {
//         for (int j = 0; j < cols; ++j)
//         {
//             Graph_lib::Point button_xy(xy.x + j * button_width, xy.y + i * button_height);
//             Graph_lib::Button button(button_xy, button_width, button_height, "Button", button_callback);
//             board.attach(button);   
//             buttons.push_back(button); 
//         }
     
//     }
// }

// void Graph_board::button_callback(Graph_lib::Address, Graph_lib::Address addr)
// {
// }

// void Graph_board::attach(Graph_lib::Widget &w)
// {
//     Widget::attach(w); // Вызов базового метода attach
// }