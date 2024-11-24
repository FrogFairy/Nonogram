#ifndef CHOOSE_LEVEL.H
#define CHOOSE_LEVEL.H

#include <string>

#include <Graph_lib/GUI.h>
#include "Main_window.h"

struct Choose_level_window: public Window_with_back
{
public:
    Choose_level_window(Graph_lib::Point xy, int w, int h, const std::string &title, const std::string &btn_label);

    static void cb_start_level(Graph_lib::Address, Graph_lib::Address addr);

    void start_level();

private:
    int w;
    int h;
    std::string title;
    std::string btn_label;
    Graph_lib::Menu level_widget;
    Graph_lib::Point p;

};

#endif