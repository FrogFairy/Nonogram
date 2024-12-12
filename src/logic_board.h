#ifndef LOGIC_BOARD_H
#define LOGIC_BOARD_H

#include "database.h"

#include <vector>

struct Position
{
    Position() : _x(0), _y(0) {};
    Position(unsigned int x, unsigned int y) : _x{x}, _y{y} {}
    unsigned int x() { return _x; }
    unsigned int y() { return _y; }

private:
    unsigned int _x;
    unsigned int _y;
};

struct Logic_board
{
public:
    enum Response {OK, MISTAKE, FINISH};

    Logic_board(Level& level) 
        : current{level.current_values}, correct{level.correct_values},
        empty{level.empty}, row_intervals{}, col_intervals{}, status{OK}
    {
        height = level.size.height();
        width = level.size.width();
        fill_col_digits();
        fill_row_digits();
        if (correct_count == finish_count) status = FINISH;
    }
     
    void set_click(Position pos, int val);
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