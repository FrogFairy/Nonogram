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
        : _current{level.current_values()}, _correct{level.correct_values()},
        _empty{level.get_empty()}, _status{OK},
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
    
    void set_click(Position pos, int val);
    Position hint_click();
    void after_hint(Position pos);
    void after_mistake(Position pos);

    std::vector<Position> changed_digits(Position pos, Level::Needful state);

    std::vector<Position> hidden_rows()
    {
        if (_inverted == Level::FILLED)
            return _hidden_fill_rows;
        return _hidden_cross_rows;
    }

    std::vector<Position> hidden_cols()
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

    unsigned int max_rows() { return _max_rows; }
    unsigned int max_cols() { return _max_cols; }

    unsigned int width() { return _width; }
    unsigned int height() { return _height; }

    std::vector<std::vector<Interval>> row_intervals() { return _row_intervals; }
    std::vector<std::vector<Interval>> col_intervals() { return _col_intervals; }

    std::vector<std::vector<int>> current() { return _current; }

    std::vector<Position> get_empty() { return _empty; }

    Response status() { return _status; }

private:
    bool col_find(Position_interval pos_interval, const std::function<bool(int)>& condition_func);

    Position row_changed(Position pos, int needful_value, int opposed_value, Level::Needful state);
    Position col_changed(Position pos, int needful_value, int opposed_value, Level::Needful state);

    void fill_row_digits();
    void fill_col_digits();

    void init_hidden_rows();
    void init_hidden_cols();

    void load_hidden_rows();
    void load_hidden_cols();

    Response _status;

    std::vector<std::vector<Interval>> _row_intervals;
    std::vector<std::vector<Interval>> _col_intervals;
    std::vector<std::vector<int>> _current;
    std::vector<Position> _empty;
    std::vector<std::vector<int>> _correct;

    std::vector<Position> _hidden_fill_rows;
    std::vector<Position> _hidden_fill_cols;
    std::vector<Position> _hidden_cross_cols;
    std::vector<Position> _hidden_cross_rows;

    std::vector<Position_interval> _buffer_rows; // buffer for hidden rows for inverted board
    std::vector<Position_interval> _buffer_cols;

    unsigned int _correct_count; // count of correct click (filled)
    unsigned int _finish_count; // count of filled cells in correct
    Level::Needful _inverted;

    unsigned int _max_rows; // maximum of digits in rows
    unsigned int _max_cols; // maximum of digits in cols
    unsigned int _width, _height;
};

#endif // LOGIC_BOARD_H
