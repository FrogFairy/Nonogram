#ifndef LOGIC_BOARD_H
#define LOGIC_BOARD_H

#include "database.h"

#include <vector>
#include <functional>

struct Nonogram_logic
{
public:
    enum Response {OK, MISTAKE, FINISH};

    Nonogram_logic(Level& level) 
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
    
    void set_cell(Position pos, Level::Cell_state val);
    void change_cell(Position pos, Level::Cell_state val);

    std::vector<Position> changed_digits(Position pos, Level::Needful state);

    std::vector<Position> hidden_rows()
    {
        if (_inverted == Level::FILLED_VAL)
            return _hidden_fill_rows;
        return _hidden_cross_rows;
    }

    std::vector<Position> hidden_cols()
    {
        if (_inverted == Level::FILLED_VAL)
            return _hidden_fill_cols;
        return _hidden_cross_cols;
    }

    void invert() 
    { 
        _inverted = (_inverted == Level::FILLED_VAL ? Level::CROSS_VAL : Level::FILLED_VAL);
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

    Level::Cell_state current(Position pos) { return _current[pos.x][pos.y]; }
    std::vector<std::vector<Level::Cell_state>> current() { return _current; }
    Level::Needful correct(Position pos) { return _correct[pos.x][pos.y]; }

    std::vector<Position> get_empty() { return _empty; }

    Response status() { return _status; }

private:
    bool col_find(Position_interval pos_interval, const std::function<bool(int)>& condition_func);

    Position row_changed(Position pos, Level::Cell_state needful_value, Level::Cell_state opposed_value, Level::Needful state);
    Position col_changed(Position pos, Level::Cell_state needful_value, Level::Cell_state opposed_value, Level::Needful state);

    void fill_row_digits();
    void fill_col_digits();

    void init_hidden_rows();
    void init_hidden_cols();

    void load_hidden_rows();
    void load_hidden_cols();

    Response _status;

    std::vector<std::vector<Interval>> _row_intervals;
    std::vector<std::vector<Interval>> _col_intervals;
    std::vector<std::vector<Level::Cell_state>> _current;
    std::vector<Position> _empty;
    std::vector<std::vector<Level::Needful>> _correct;

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

struct Prompter
{
    Prompter() 
        : logic_board{nullptr} {}
        
    Prompter(Nonogram_logic& logic_board)
        : logic_board{&logic_board} {}
    
    Prompter& operator=(const Prompter& other)
    {
        logic_board = other.logic_board;
        return *this;
    }
    
    Position get_hint();
    void after_hint(Position pos);

private:
    Nonogram_logic* logic_board;
};

#endif // LOGIC_BOARD_H
