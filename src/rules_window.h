#ifndef RULES_WINDOW.H
#define RULES_WINDOW .H

#include "main_window.h"

struct Rules_window : public Window_with_back
{
public:
    Rules_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper& own);
private:
    int w;
    int h;
    Graph_lib::Text rt;
    Graph_lib::Text rt_1;
    Graph_lib::Text rt_2;
    Graph_lib::Text rt_3;
    Graph_lib::Text rt_4;
    Graph_lib::Text rt_5;
    Windows_wrapper &own;
    Graph_lib::Point xy;
    std::string title;  //переписать правила
};

#endif