#ifndef RULES_WINDOW_H
#define RULES_WINDOW_H

#include "main_window.h"

struct Rules_window : public Window_with_back
{
public:
    Rules_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper& own);
    
private:
    Graph_lib::Text rt;
    Graph_lib::Image rules;
    Windows_wrapper &own;
};

#endif // RULES_WINDOW_H