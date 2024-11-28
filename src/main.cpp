#include "wrapper.h"


int main()
{
    Windows_wrapper win{Graph_lib::Point{400, 100}, 700, 700, "window"};
    return Graph_lib::gui_main();
}