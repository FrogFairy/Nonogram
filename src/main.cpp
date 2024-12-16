#include "wrapper.h"
#include "logic_board.h"
#include "database.h"

#include <ctime>
#include <iostream>

int main()
try
{
    srand(time(0));

    Windows_wrapper win{Graph_lib::Point{400, 100}, 700, 700, "Nonogram"};
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