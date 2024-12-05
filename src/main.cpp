#include "wrapper.h"
#include "logic_board.h"
#include "database.h"

#include <ctime>

int main()
{
    // srand(time(0));
    // Database_levels db{};
    // Level level = db.get_level("10x10", "level 1");
    // std::vector<std::vector<int>> corr = level.correct_values;
    // auto cur1 = corr;
    // std::vector<std::vector<int>> cur2(corr.size(), std::vector<int>(corr.size(), -1));
    // Logic_board board{level};
    // std::cout << board.set_click(0, 0, 1) << std::endl;
    // Logic_board board1{level};
    // std::cout << board1.set_click(1, 2, 1) << std::endl;

    // std::vector<int> pos = board1.hint_click();
    // std::cout << pos[0] << " " << pos[1] << std::endl;
    // board1.after_hint(pos);
    // std::cout << board1.get_current()[pos[0]][pos[1]] << " " << board1.get_correct()[pos[0]][pos[1]]<< std::endl;

    Windows_wrapper win{Graph_lib::Point{400, 100}, 700, 700, "window"};
    return Graph_lib::gui_main();
}