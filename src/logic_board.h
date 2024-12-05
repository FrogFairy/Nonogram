#ifndef LOGIC_BOARD_H
#define LOGIC_BOARD_H

#include "database.h"

#include <vector>

struct Logic_board
{
public:
    Logic_board(Level& level) 
        : current{level.current_values}, correct{level.correct_values},
        empty{level.empty}
    {}
    
    bool set_click(int x, int y, int val);
    std::vector<int> hint_click();
    void after_hint(std::vector<int> position);

    std::vector<std::vector<int>> get_current()
    {
        return current;
    }

    std::vector<std::vector<int>> get_correct()
    {
        return correct;
    }

private:
    std::vector<std::vector<int>> current;
    std::vector<std::vector<int>> correct;
    std::vector<std::vector<int>> empty;
    int correct_count = 0;
};

#endif // LOGIC_BOARD_H
