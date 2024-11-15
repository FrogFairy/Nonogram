#include "Main_window.h"


int main()
{
    Main_window win{Graph_lib::Point{400, 100}, 700, 700, "window"};
    return Graph_lib::gui_main();
}