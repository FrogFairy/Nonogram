#include "nonogram_logic.h"

#include <random>
#include <algorithm>

void Nonogram_logic::fill_row_digits()
{
    _correct_count = 0;
    _finish_count = 0;
    _max_rows = 0;
    _row_intervals = {};

    int needful_value = (_inverted == Level::FILLED_VAL ? Level::FILLED : Level::CROSS);
    int opposed_value = (_inverted == Level::FILLED_VAL ? Level::CROSS : Level::FILLED);

    for (int i = 0; i < _correct.size(); ++i)
    {
        std::vector<Interval> intervals {};
        int start = -1;
        for (int j = 0; j < _correct[0].size(); ++j)
        {
            if (_correct[i][j] == Level::FILLED_VAL)
                ++_finish_count;
            if (_correct[i][j] == needful_value)
            {
                if (start < 0)
                    start = j;
            }
            if (start >= 0 && (_correct[i][j] == opposed_value || j == _correct[0].size() - 1))
            {
                if (_correct[i][j] == opposed_value)
                    intervals.push_back(Interval {start, j - 1});
                else 
                    intervals.push_back(Interval {start, j});
                start = -1;
            }
            if (int(_current[i][j]) % 2 == 1) ++_correct_count;
        }
        unsigned int opposed_rows = intervals.empty() ? 1 : intervals.size() - 1;
        if (!intervals.empty())
        {
            if (intervals[0].start != 0) ++opposed_rows;
            if (intervals[intervals.size() - 1].end != _width - 1) ++opposed_rows;
        }

        if (intervals.empty())
        {
            intervals.push_back(Interval{});
        }

        _row_intervals.push_back(intervals);
        _max_rows = std::max(_max_rows, std::max(unsigned(intervals.size()), opposed_rows));
    }
}

void Nonogram_logic::fill_col_digits()
{
    _max_cols = 0;
    _col_intervals = {};

    int needful_value = (_inverted == Level::FILLED_VAL ? Level::FILLED : Level::CROSS);
    int opposed_value = (_inverted == Level::FILLED_VAL ? Level::CROSS : Level::FILLED);

    for (int i = 0; i < _correct[0].size(); ++i)
    {
        std::vector<Interval> intervals {};
        int end = -1;
        for (int j = _correct.size() - 1; j >= 0; --j)
        {
            if (_correct[j][i] == needful_value)
            {
                if (end < 0)
                    end = j;
            }
            if (end >= 0 && (_correct[j][i] == opposed_value || j == 0))
            {
                if (_correct[j][i] == opposed_value)
                    intervals.push_back(Interval {j + 1, end});
                else 
                    intervals.push_back(Interval {j, end});
                end = -1;
            }
        }
        unsigned int opposed_cols = intervals.empty() ? 1 : intervals.size() - 1;
        if (!intervals.empty())
        {
            if (intervals[0].end != _height - 1) ++opposed_cols;
            if (intervals[intervals.size() - 1].start != 0) ++opposed_cols;
        }

        if (intervals.empty())
        {
            intervals.push_back(Interval {});
        }
        _col_intervals.push_back(intervals);
        _max_cols = std::max(_max_cols, std::max(unsigned(intervals.size()), opposed_cols));
    }  
}

void Nonogram_logic::init_hidden_rows()
{
    _hidden_fill_rows = {};
    _hidden_cross_rows = {};
    _buffer_rows = {};

    for (int i = 0; i < _row_intervals.size(); ++i)
    {
        int prev = 0;
        for (int j = 0; j < _row_intervals[i].size(); ++j)
        {
            Interval interval = _row_intervals[i][j];
            if (interval.empty())
            {
                if (_inverted == Level::FILLED_VAL)
                    _hidden_fill_rows.push_back(Position {i, j});
                else
                    _hidden_cross_rows.push_back(Position {i, j});
                prev = _width;

                if (std::find_if(&_current[i][0], &_current[i][_width - 1] + 1, 
                    [&](int val){ return _inverted == Level::FILLED_VAL && (val % 2) != 0
                                  || _inverted == Level::CROSS_VAL && (val == -1 || (val % 2) == 0); }) == &_current[i][_width - 1] + 1)
                {
                    if (_inverted == Level::CROSS_VAL)
                        _hidden_fill_rows.push_back(Position {i, 0});
                    else
                        _hidden_cross_rows.push_back(Position {i, 0});
                }

                continue;
            }
            if (interval.start == 0 && interval.end == _width - 1)
            {
                if (_inverted == Level::CROSS_VAL)
                    _hidden_fill_rows.push_back(Position {i, j});
                else
                    _hidden_cross_rows.push_back(Position {i, j});
            }

            if (std::find_if(&_current[i][interval.start], &_current[i][interval.end] + 1, 
                    [&](int val){ return _inverted == Level::FILLED_VAL && (val == -1 || (val % 2) == 0) 
                                  || _inverted == Level::CROSS_VAL && (val % 2) != 0; }) == &_current[i][interval.end] + 1)
            {
                if (_inverted == Level::FILLED_VAL)
                    _hidden_fill_rows.push_back(Position {i, j});
                else
                    _hidden_cross_rows.push_back(Position {i, j});
            }
            if (interval.start > 0 && std::find_if(&_current[i][prev], &_current[i][interval.start], 
                    [&](int val){ return _inverted == Level::FILLED_VAL && (val % 2) != 0
                                  || _inverted == Level::CROSS_VAL && (val == -1 || (val % 2) == 0); }) == &_current[i][interval.start])
            {
                _buffer_rows.push_back(Position_interval {i, prev, interval.start - 1});
            }
            prev = interval.end + 1;
        }

        if (prev < _width)
        {
            if (std::find_if(&_current[i][prev], &_current[i][_width - 1] + 1, 
                    [&](int val){ return _inverted == Level::FILLED_VAL && (val % 2) != 0
                                  || _inverted == Level::CROSS_VAL && (val == -1 || (val % 2) == 0); }) == &_current[i][_width - 1] + 1)
                _buffer_rows.push_back(Position_interval {i, prev, (int) (_width - 1)});
        }
    }
}

bool Nonogram_logic::col_find(Position_interval pos_interval, const std::function<bool(int)>& condition_func)
{
    std::vector<int> vec = {};
    for (int i = pos_interval.interval.start; i < pos_interval.interval.end; ++i)
    {
        vec.push_back(_current[i][pos_interval.pos]);
    }
    return std::find_if(&vec[0], &vec[vec.size() - 1] + 1, condition_func) == &vec[vec.size() - 1] + 1;
}

void Nonogram_logic::init_hidden_cols()
{
    _hidden_fill_cols = {};
    _hidden_cross_cols = {};
    _buffer_cols = {};

    for (int i = 0; i < _col_intervals.size(); ++i)
    {
        int prev = 0;
        for (int j = _col_intervals[i].size() - 1; j >= 0; --j)
        {
            Interval interval = _col_intervals[i][j];
            if (interval.empty())
            {
                if (_inverted == Level::FILLED_VAL)
                    _hidden_fill_cols.push_back(Position {i, j});
                else
                    _hidden_cross_cols.push_back(Position {i, j});
                prev = _height;

                if (col_find(Position_interval {i, 0, int(_height)}, 
                            [&](int val){ return _inverted == Level::FILLED_VAL && (val % 2) != 0
                                  || _inverted == Level::CROSS_VAL && (val == -1 || (val % 2) == 0); }))
                {
                    if (_inverted == Level::CROSS_VAL)
                        _hidden_fill_cols.push_back(Position {i, 0});
                    else
                        _hidden_cross_cols.push_back(Position {i, 0});
                }

                continue;
            }
            if (interval.start == 0 && interval.end == _height - 1)
            {
                if (_inverted == Level::CROSS_VAL)
                    _hidden_fill_cols.push_back(Position {i, j});
                else
                    _hidden_cross_cols.push_back(Position {i, j});
            }

            if(col_find(Position_interval{i, interval.start, interval.end + 1}, 
                            [&](int val){ return _inverted == Level::FILLED_VAL && (val == -1 || (val % 2) == 0) 
                                  || _inverted == Level::CROSS_VAL && (val % 2) != 0; }))
            {
                if (_inverted == Level::FILLED_VAL)
                    _hidden_fill_cols.push_back(Position {i, j});
                else
                    _hidden_cross_cols.push_back(Position {i, j});
            }
            if(interval.start > 0 && col_find(Position_interval{i, prev, interval.start},
                    [&](int val){ return _inverted == Level::FILLED_VAL && (val % 2) != 0
                                  || _inverted == Level::CROSS_VAL && (val == -1 || (val % 2) == 0); }))
            {
                _buffer_cols.push_back({i, prev, interval.start - 1});
            }

            prev = interval.end + 1;
        }

        if (prev < _height)
        {
            if (col_find(Position_interval{i, prev, int(_height)}, 
                [&](int val){ return _inverted == Level::FILLED_VAL && (val % 2) != 0
                                  || _inverted == Level::CROSS_VAL && (val == -1 || (val % 2) == 0); }))
            {
                _buffer_cols.push_back({i, prev, int(_height - 1)});
            }

        }
    }
}

void Nonogram_logic::load_hidden_rows()
{
    for (Position_interval pos_interval : _buffer_rows)
    {
        int x = pos_interval.pos, left = pos_interval.interval.start, right = pos_interval.interval.end;
        int col = std::find(_row_intervals[x].begin(), _row_intervals[x].end(), Interval {left, right}) - _row_intervals[x].begin();
        Position res = {x, col};
        if (_inverted == Level::FILLED_VAL)
            _hidden_fill_rows.push_back(res);
        else
            _hidden_cross_rows.push_back(res);
    }
    _buffer_rows = {};
}

void Nonogram_logic::load_hidden_cols()
{
    for (Position_interval pos_interval : _buffer_cols)
    {
        int y = pos_interval.pos, up = pos_interval.interval.start, down = pos_interval.interval.end;
        int row = std::find(_col_intervals[y].begin(), _col_intervals[y].end(), Interval {up, down}) - _col_intervals[y].begin();
        Position res = {y, row};
        if (_inverted == Level::FILLED_VAL)
            _hidden_fill_cols.push_back(res);
        else
            _hidden_cross_cols.push_back(res);
    }
    _buffer_cols = {};
}

Position Nonogram_logic::row_changed(Position pos, Level::Cell_state needful_value, Level::Cell_state opposed_value, Level::Needful state)
{
    Position res {};
    int x = pos.x, y = pos.y;

    if (_current[x][y] % 2 != needful_value) return res;

    int left = y, right = y;
    while (true)
    {
        if ((left == 0 || left > 0 && (_current[x][left - 1] < 0 || _current[x][left - 1] % 2 == opposed_value)) &&
            (right == _width - 1 || right < _width - 1 && (_current[x][right + 1] < 0 || _current[x][right + 1] % 2 == opposed_value)))
            break;
        if (left > 0 && _current[x][left - 1] >= 0 && _current[x][left - 1] % 2 == needful_value && _current[x][left - 1] != -1)
            --left;
        if (right < _width - 1 && _current[x][right + 1] >= 0 && _current[x][right + 1] % 2 == needful_value && _current[x][right + 1] != -1)
            ++right;
    }

    if ((left == 0 || left > 0 && _correct[x][left - 1] % 2 == opposed_value) && 
        (right == _width - 1 || right < _width - 1 && _correct[x][right + 1] % 2 == opposed_value))
    {
        int col = 0;
        if (state == _inverted)
        {
            col = std::find(_row_intervals[x].begin(), _row_intervals[x].end(), Interval {left, right}) - _row_intervals[x].begin();
            res = {x, col};
            if (state == Level::FILLED_VAL)
                _hidden_fill_rows.push_back(res);
            else
                _hidden_cross_rows.push_back(res);
        }
        else
        {
            _buffer_rows.push_back(Position_interval {x, left, right});
        }
    }
    return res;
}

Position Nonogram_logic::col_changed(Position pos, Level::Cell_state needful_value, Level::Cell_state opposed_value, Level::Needful state)
{
    Position res {};
    int x = pos.x, y = pos.y;

    if (_current[x][y] % 2 != needful_value) return res;

    int down = x, up = x;
    while (true)
    {
        if ((up == 0 || up > 0 && (_current[up - 1][y] < 0 || _current[up - 1][y] % 2 == opposed_value)) &&
            (down == _height - 1 || down < _height - 1 && (_current[down + 1][y] < 0 || _current[down + 1][y] % 2 == opposed_value)))
            break;
        if (up > 0 && _current[up - 1][y] >= 0 && _current[up - 1][y] % 2 == needful_value && _current[up - 1][y] != -1)
            --up;
        if (down < _height - 1 && _current[down + 1][y] >= 0 && _current[down + 1][y] % 2 == needful_value && _current[down + 1][y] != -1)
            ++down;
    }

    if ((up == 0 || up > 0 && _correct[up - 1][y] % 2 == opposed_value) && 
        (down == _height - 1 || down < _height - 1 && _correct[down + 1][y] % 2 == opposed_value))
    {
        if (state == _inverted)
        {
            int row = std::find(_col_intervals[y].begin(), _col_intervals[y].end(), Interval {up, down}) - _col_intervals[y].begin();
            res = {y, row};
            if (state == Level::FILLED_VAL)
                _hidden_fill_cols.push_back(res);
            else
                _hidden_cross_cols.push_back(res);
        }
        else
        {
            _buffer_cols.push_back(Position_interval {y, up, down});
        }
    }

    return res;
}

std::vector<Position> Nonogram_logic::changed_digits(Position pos, Level::Needful state)
{
    Level::Cell_state needful_value = (state == Level::FILLED_VAL ? Level::FILLED : Level::CROSS);
    Level::Cell_state opposed_value = (state == Level::FILLED_VAL ? Level::CROSS : Level::FILLED);

    int x = pos.x, y = pos.y;

    std::vector<Position> res (2, Position {});
    if (_current[x][y] < 0 || _current[x][y] % 2 == opposed_value) return res;

    res[0] = row_changed(pos, needful_value, opposed_value, state);
    res[1] = col_changed(pos, needful_value, opposed_value, state);

    return res;
}

void Nonogram_logic::set_cell(Position pos, Level::Cell_state val)
{
    int x = pos.x, y = pos.y;

    if (_current[x][y] == -1)
    {
        _current[x][y] = val;
        _empty.erase(std::find(_empty.begin(), 
                    _empty.end(), Position {x, y}));
        if (_correct[x][y] == Level::FILLED_VAL) ++_correct_count;
    }
    _status = (_correct_count == _finish_count ? FINISH : (int(_current[x][y]) % 2 == int(_correct[x][y]) % 2 ? OK : MISTAKE));
    if (_status == MISTAKE)
        _current[x][y] = Level::Cell_state(int(_correct[x][y]) + 4);
}

void Nonogram_logic::change_cell(Position pos, Level::Cell_state val)
{
    _current[pos.x][pos.y] = val;
}

Position Prompter::get_hint()
{
    if (logic_board->status() == Nonogram_logic::FINISH) 
        return Position {};
    
    auto _empty = logic_board->get_empty();
    int rand_ind = std::rand() % _empty.size();
    Position pos = _empty[rand_ind];
    Level::Cell_state val = (logic_board->correct(pos) == Level::FILLED_VAL ? Level::HINT_FILLED : Level::HINT_CROSS);
    logic_board->set_cell(pos, val);

    return pos;
}

void Prompter::after_hint(Position pos)
{
    Level::Cell_state val = (logic_board->current(pos) == Level::HINT_FILLED ? Level::FILLED : Level::CROSS);
    logic_board->change_cell(pos, val);
}