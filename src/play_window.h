#ifndef PLAY_WINDOW.H
#define PLAY_WINDOW.H

#include <string>
#include <vector>

#include "main_window.h"
#include "graph_board.h"
#include "buttons.h"

struct Play_window : public Window_with_back
{
public:
    Play_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper &own);

    

protected:
    Graph_board board;
    int rows, cols;
    int w;
    int h;
    Graph_lib::Lines b_cross;
    Windows_wrapper& own;
    Graph_lib::Point xy;
    std::string title;
    Graph_lib::Button rules_button;
    Graph_lib::Button hint_button;
    Graph_lib::Image lamp;
    Graph_lib::Button restart_button;
    Fill_Button fill_button;
    Graph_lib::Button cross_button;
    Graph_lib::Vector_ref<Graph_lib::Image> hearts_img;
    void rules();
    static void cb_rules(Graph_lib::Address, Graph_lib::Address addr);
    void hint();
    static void cb_hint(Graph_lib::Address, Graph_lib::Address addr);
    void restart();
    static void cb_restart(Graph_lib::Address, Graph_lib::Address addr);
    void fill();
    static void cb_fill(Graph_lib::Address, Graph_lib::Address addr);
    void cross();
    static void cb_cross(Graph_lib::Address, Graph_lib::Address addr);

};


#endif