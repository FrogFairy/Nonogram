
#include <iostream>
#include <Graph_lib/GUI.h>
#include <Graph_lib/Window.h>
#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

#include "Main_window.h"


int main()
{
    Main_window win{Graph_lib::Point{400, 100}, 700, 700, "window"};
    return Graph_lib::gui_main();
}