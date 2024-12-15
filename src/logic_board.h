#ifndef LOGIC_BOARD_H
#define LOGIC_BOARD_H

#include "database.h"

#include <vector>
#include <functional>

struct Logic_board
{
public:
    enum Response {OK, MISTAKE, FINISH};

    Logic_board(Level& level) 
        : current{level.current_values()}, correct{level.correct_values()},
        empty{level.empty()}, status{OK},
        inverted{level.inverted}
    {
        height = level.size.height;
        width = level.size.width;
        fill_col_digits();
        fill_row_digits();
        init_hidden_rows();
        init_hidden_cols();
        if (correct_count == finish_count) status = FINISH;
    }
    
    void set_click(int x, int y, int val);
    std::vector<int> hint_click();
    void after_hint(std::vector<int> position);
    void after_mistake(std::vector<int> position);

    std::vector<std::vector<int>> changed_digits(int x, int y, Level::Needful state);

    std::vector<std::vector<int>> hidden_rows()
    {
        if (inverted == Level::FILLED)
            return hidden_fill_rows;
        return hidden_cross_rows;
    }

    std::vector<std::vector<int>> hidden_cols()
    {
        if (inverted == Level::FILLED)
            return hidden_fill_cols;
        return hidden_cross_cols;
    }

    void hidden_rows_add(std::vector<int>& position)
    {
        if (inverted == Level::FILLED)
            hidden_fill_rows.push_back(position);
        else
            hidden_cross_rows.push_back(position);
    }

    void hidden_cols_add(std::vector<int>& position)
    {
        if (inverted == Level::FILLED)
            hidden_fill_cols.push_back(position);
        else
            hidden_cross_cols.push_back(position);
    }

    void invert() 
    { 
        inverted = (inverted == Level::FILLED ? Level::CROSS : Level::FILLED);
        fill_row_digits();
        fill_col_digits();
        load_hidden_rows();
        load_hidden_cols();
    }

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
    bool col_find(int row, int start, int end, const std::function<bool(int)>& condition_func);

    std::vector<int> row_changed(int x, int y, int needful_value, int opposed_value, Level::Needful state);
    std::vector<int> col_changed(int x, int y, int needful_value, int opposed_value, Level::Needful state);

    void fill_row_digits();
    void fill_col_digits();

    void init_hidden_rows();
    void init_hidden_cols();

    void load_hidden_rows();
    void load_hidden_cols();

    std::vector<std::vector<int>> hidden_fill_rows;
    std::vector<std::vector<int>> hidden_fill_cols;
    std::vector<std::vector<int>> hidden_cross_cols;
    std::vector<std::vector<int>> hidden_cross_rows;

    std::vector<std::vector<int>> buffer_rows; // buffer for hidden rows for inverted board
    std::vector<std::vector<int>> buffer_cols;

    int correct_count = 0; // count of correct click (filled)
    int finish_count = 0; // count of filled cells in correct
    Level::Needful inverted;
};

#endif // LOGIC_BOARD_H
