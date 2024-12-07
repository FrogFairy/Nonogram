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
    Graph_lib::Image rules;
    Windows_wrapper &own;
    Graph_lib::Point xy;
    std::string title;  //переписать правила
};

#endif