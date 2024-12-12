#ifndef NONOGRAM_LOGIC_H
#define NONOGRAM_LOGIC_H

#include "database.h"

#include <vector>

struct Position
{
    unsigned int x;
    unsigned int y;
};

struct Nonogram_logic
{
public:
    enum Response {OK, MISTAKE, FINISH};

    Nonogram_logic(Level& level) 
        : current{level.current_values}, correct{level.correct_values},
        empty{level.empty}, row_intervals{}, col_intervals{}, status{OK}
    {
        height = level.size.height();
        width = level.size.width();
        fill_col_digits();
        fill_row_digits();
        if (correct_count == finish_count) status = FINISH;
    }
     
    void set_cell(Position pos, int val);
    Position hint_click();
    void after_hint(Position pos);
    void after_mistake(Position pos);

    Position row_changed(Position pos);
    Position col_changed(Position pos);
    std::vector<Position> changed_digits(Position pos);

    void fill_row_digits();
    void fill_col_digits();

    int max_rows  = 0; // maximum of digits in rows
    int max_cols = 0; // maximum of digits in cols

    int width, height;
    
    std::vector<std::vector<Position>> row_intervals;
    std::vector<std::vector<Position>> col_intervals;
    std::vector<std::vector<int>> current;
    std::vector<std::vector<int>> correct;
    std::vector<Position> empty;

    Response status;

private:
    int correct_count = 0; // count of correct click (filled)
    int finish_count = 0; // count of filled cells in correct
};

#endif // NONOGRAM_LOGIC_H