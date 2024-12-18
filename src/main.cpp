#include "wrapper.h"
#include "logic_board.h"
#include "database.h"

#include <ctime>
#include <iostream>

int main()
try
{
    srand(time(0));

    Windows_wrapper win{window_point, window_width, window_height, "Nonogram"};
    return Graph_lib::gui_main();
}
catch (Exit_exception& e)
{
    return 0;
}
catch (...)
{
    std::cerr << "Something went wrong..." << std::endl;
    return 1;
}