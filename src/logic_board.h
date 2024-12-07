#ifndef LOGIC_BOARD_H
#define LOGIC_BOARD_H

#include "database.h"

#include <vector>

struct Logic_board
{
public:
    Logic_board(Level& level) 
        : current{level.current_values}, correct{level.correct_values},
        empty{level.empty}, row_digits{}, col_digits{}
    {
        fill_col_digits();
        fill_row_digits();    
    }
    
    bool set_click(int x, int y, int val);
    std::vector<int> hint_click();
    void after_hint(std::vector<int> position);

    void fill_row_digits();
    void fill_col_digits();

    int max_rows  = 0; // maximum of digits in rows
    int max_cols = 0; // maximum of digits in cols
    
    std::vector<std::vector<int>> row_digits;
    std::vector<std::vector<int>> col_digits;
    std::vector<std::vector<int>> current;
    std::vector<std::vector<int>> correct;

private:
    std::vector<std::vector<int>> empty;
    int correct_count = 0;
};

#endif // LOGIC_BOARD_H
