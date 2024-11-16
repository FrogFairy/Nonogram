#ifndef GENERATE_LEVEL.H
#define GENERATE_LEVEL.H

#include <string>

#include <Graph_lib/GUI.h>
#include "Main_window.h"

struct Generate_level_window: public Window_with_back
{
public:
    Generate_level_window(Graph_lib::Point xy, int w, int h, const std::string &title);

private:
    Graph_lib::Choice_box size_box;
    Graph_lib::Point p;
    int w;
    int h;
    std::string title;
};

#endif 