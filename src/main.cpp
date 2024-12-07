#include "wrapper.h"
#include "logic_board.h"
#include "database.h"

#include <ctime>

int main()
{
    Windows_wrapper win{Graph_lib::Point{400, 100}, 700, 700, "window"};
    return Graph_lib::gui_main();
}