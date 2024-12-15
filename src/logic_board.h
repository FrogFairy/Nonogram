#ifndef LOGIC_BOARD_H
#define LOGIC_BOARD_H

#include "database.h"

#include <vector>
#include <functional>

struct Position
{
    int x;
    int y;
};

struct Position_interval
{
    enum Type {COLUMN, ROW};
    Position pos;
    Type tp;
};

struct Logic_board
{
public:
    enum Response {OK, MISTAKE, FINISH};

    Logic_board(Level& level) 
        : _current{level.current_values()}, _correct{level.correct_values()},
        _empty{level.empty()}, _status{OK},
        _inverted{level.inverted}
    {
        _height = level.size.height;
        _width = level.size.width;
        fill_col_digits();
        fill_row_digits();
        init_hidden_rows();
        init_hidden_cols();
        if (_correct_count == _finish_count) _status = FINISH;
    }
    
    void set_click(int x, int y, int val);
    std::vector<int> hint_click();
    void after_hint(std::vector<int> position);
    void after_mistake(std::vector<int> position);

    std::vector<std::vector<int>> changed_digits(int x, int y, Level::Needful state);

    std::vector<std::vector<int>> hidden_rows()
    {
        if (_inverted == Level::FILLED)
            return _hidden_fill_rows;
        return _hidden_cross_rows;
    }

    std::vector<std::vector<int>> hidden_cols()
    {
        if (_inverted == Level::FILLED)
            return _hidden_fill_cols;
        return _hidden_cross_cols;
    }

    void invert() 
    { 
        _inverted = (_inverted == Level::FILLED ? Level::CROSS : Level::FILLED);
        fill_row_digits();
        fill_col_digits();
        load_hidden_rows();
        load_hidden_cols();
    }

    int max_rows() { return _max_rows; }
    int max_cols() { return _max_cols; }

    int width() { return _width; }
    int height() { return _height; }

    std::vector<std::vector<std::vector<int>>> row_intervals() { return _row_intervals; }
    std::vector<std::vector<std::vector<int>>> col_intervals() { return _col_intervals; }

    std::vector<std::vector<int>> current() { return _current; }

    std::vector<std::vector<int>> empty() { return _empty; }

    Response status() { return _status; }

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

    Response _status;

    std::vector<std::vector<std::vector<int>>> _row_intervals;
    std::vector<std::vector<std::vector<int>>> _col_intervals;
    std::vector<std::vector<int>> _current;
    std::vector<std::vector<int>> _empty;
    std::vector<std::vector<int>> _correct;

    std::vector<std::vector<int>> _hidden_fill_rows;
    std::vector<std::vector<int>> _hidden_fill_cols;
    std::vector<std::vector<int>> _hidden_cross_cols;
    std::vector<std::vector<int>> _hidden_cross_rows;

    std::vector<std::vector<int>> _buffer_rows; // buffer for hidden rows for inverted board
    std::vector<std::vector<int>> _buffer_cols;

    int _correct_count; // count of correct click (filled)
    int _finish_count; // count of filled cells in correct
    Level::Needful _inverted;

    int _max_rows; // maximum of digits in rows
    int _max_cols; // maximum of digits in cols
    int _width, _height;
};

#endif // LOGIC_BOARD_H
