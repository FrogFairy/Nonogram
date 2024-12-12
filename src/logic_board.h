#ifndef LOGIC_BOARD_H
#define LOGIC_BOARD_H

#include "database.h"

#include <vector>

struct Logic_board
{
public:
    enum Response {OK, MISTAKE, FINISH};

    Logic_board(Level& level) 
        : current{level.current_values}, correct{level.correct_values},
        empty{level.empty}, row_intervals{}, col_intervals{}, status{OK}
    {
        height = level.size.height;
        width = level.size.width;
        fill_col_digits();
        fill_row_digits();
        if (correct_count == finish_count) status = FINISH;
    }
    
    void set_click(int x, int y, int val);
    std::vector<int> hint_click();
    void after_hint(std::vector<int> position);
    void after_mistake(std::vector<int> position);

    std::vector<int> row_changed(int x, int y);
    std::vector<int> col_changed(int x, int y);
    std::vector<std::vector<int>> changed_digits(int x, int y);

    void fill_row_digits();
    void fill_col_digits();

    int max_rows  = 0; // maximum of digits in rows
    int max_cols = 0; // maximum of digits in cols

    int width, height;
    
    std::vector<std::vector<std::vector<int>>> row_intervals;
    std::vector<std::vector<std::vector<int>>> col_intervals;
    std::vector<std::vector<int>> current;
    std::vector<std::vector<int>> correct;
    std::vector<std::vector<int>> empty;

    Response status;

private:
    int correct_count = 0; // count of correct click (filled)
    int finish_count = 0; // count of filled cells in correct
};

#endif // LOGIC_BOARD_H
