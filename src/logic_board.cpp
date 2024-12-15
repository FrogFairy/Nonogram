#include "logic_board.h"

#include <random>
#include <algorithm>

void Logic_board::fill_row_digits()
{
    correct_count = 0;
    finish_count = 0;
    row_intervals = {};
    int needful_value = (inverted == Level::FILLED ? 1 : 0);
    int opposed_value = (inverted == Level::FILLED ? 0 : 1);

    for (int i = 0; i < correct.size(); ++i)
    {
        std::vector<std::vector<int>> intervals {};
        int start = -1;
        for (int j = 0; j < correct[0].size(); ++j)
        {
            if (correct[i][j] == 1)
                ++finish_count;
            if (correct[i][j] == needful_value)
            {
                if (start < 0)
                    start = j;
            }
            if (start >= 0 && (correct[i][j] == opposed_value || j == correct[0].size() - 1))
            {
                if (correct[i][j] == opposed_value)
                    intervals.push_back(std::vector<int> {start, j - 1});
                else 
                    intervals.push_back(std::vector<int> {start, j});
                start = -1;
            }
            if (current[i][j] == 1) ++correct_count;
        }
        if (!intervals.size())
        {
            intervals.push_back(std::vector<int>{});
        }
        row_intervals.push_back(intervals);
        max_rows = std::max(max_rows, (int) intervals.size());
    }
}

void Logic_board::fill_col_digits()
{
    col_intervals = {};
    int needful_value = (inverted == Level::FILLED ? 1 : 0);
    int opposed_value = (inverted == Level::FILLED ? 0 : 1);

    for (int i = 0; i < correct[0].size(); ++i)
    {
        std::vector<std::vector<int>> intervals {};
        int end = -1;
        for (int j = correct.size() - 1; j >= 0; --j)
        {
            if (correct[j][i] == needful_value)
            {
                if (end < 0)
                    end = j;
            }
            if (end >= 0 && (correct[j][i] == opposed_value || j == 0))
            {
                if (correct[j][i] == opposed_value)
                    intervals.push_back(std::vector<int> {j + 1, end});
                else 
                    intervals.push_back(std::vector<int> {j, end});
                end = -1;
            }
        }
        if (!intervals.size())
        {
            intervals.push_back(std::vector<int> {});
        }
        col_intervals.push_back(intervals);
        max_cols = std::max(max_cols, (int) intervals.size());
    }  
}

void Logic_board::init_hidden_rows()
{
    hidden_fill_rows = {};
    hidden_cross_rows = {};
    buffer_rows = {};

    for (int i = 0; i < row_intervals.size(); ++i)
    {
        int prev = 0;
        for (int j = 0; j < row_intervals[i].size(); ++j)
        {
            std::vector<int> interval = row_intervals[i][j];
            if (interval.empty())
            {
                if (inverted == Level::FILLED)
                    hidden_fill_rows.push_back(std::vector<int> {i, j});
                else
                    hidden_cross_rows.push_back(std::vector<int> {i, j});
                prev = width;

                if (std::find_if(&current[i][0], &current[i][width - 1] + 1, 
                    [&](int val){ return inverted == Level::FILLED && (val % 2) != 0
                                  || inverted == Level::CROSS && (val == -1 || (val % 2) == 0); }) == &current[i][width - 1] + 1)
                {
                    if (inverted == Level::CROSS)
                        hidden_fill_rows.push_back(std::vector<int> {i, 0});
                    else
                        hidden_cross_rows.push_back(std::vector<int> {i, 0});
                }

                continue;
            }
            if (interval[0] == 0 && interval[1] == width - 1)
            {
                if (inverted == Level::CROSS)
                    hidden_fill_rows.push_back(std::vector<int> {i, j});
                else
                    hidden_cross_rows.push_back(std::vector<int> {i, j});
            }

            if (std::find_if(&current[i][interval[0]], &current[i][interval[1]] + 1, 
                    [&](int val){ return inverted == Level::FILLED && (val == -1 || (val % 2) == 0) 
                                  || inverted == Level::CROSS && (val % 2) != 0; }) == &current[i][interval[1]] + 1)
            {
                if (inverted == Level::FILLED)
                    hidden_fill_rows.push_back(std::vector<int> {i, j});
                else
                    hidden_cross_rows.push_back(std::vector<int> {i, j});
            }
            if (interval[0] > 0 && std::find_if(&current[i][prev], &current[i][interval[0]], 
                    [&](int val){ return inverted == Level::FILLED && (val % 2) != 0
                                  || inverted == Level::CROSS && (val == -1 || (val % 2) == 0); }) == &current[i][interval[0]])
            {
                buffer_rows.push_back({i, prev, interval[0] - 1});
            }
            prev = interval[1] + 1;
        }

        if (prev < width)
        {
            if (std::find_if(&current[i][prev], &current[i][width - 1] + 1, 
                    [&](int val){ return inverted == Level::FILLED && (val % 2) != 0
                                  || inverted == Level::CROSS && (val == -1 || (val % 2) == 0); }) == &current[i][width - 1] + 1)
                buffer_rows.push_back({i, prev, width - 1});
        }
    }
}

bool Logic_board::col_find(int col, int start, int end, const std::function<bool(int)>& condition_func)
{
    std::vector<int> vec = {};
    for (int i = start; i < end; ++i)
    {
        vec.push_back(current[i][col]);
    }
    return std::find_if(&vec[0], &vec[vec.size() - 1] + 1, condition_func) == &vec[vec.size() - 1] + 1;
}

void Logic_board::init_hidden_cols()
{
    hidden_fill_cols = {};
    hidden_cross_cols = {};
    buffer_cols = {};

    for (int i = 0; i < col_intervals.size(); ++i)
    {
        int prev = 0;
        for (int j = col_intervals[i].size() - 1; j >= 0; --j)
        {
            std::vector<int> interval = col_intervals[i][j];
            if (interval.empty())
            {
                if (inverted == Level::FILLED)
                    hidden_fill_cols.push_back(std::vector<int> {i, j});
                else
                    hidden_cross_cols.push_back(std::vector<int> {i, j});
                prev = height;

                if (col_find(i, 0, height, 
                            [&](int val){ return inverted == Level::FILLED && (val % 2) != 0
                                  || inverted == Level::CROSS && (val == -1 || (val % 2) == 0); }))
                {
                    if (inverted == Level::CROSS)
                        hidden_fill_cols.push_back(std::vector<int> {i, 0});
                    else
                        hidden_cross_cols.push_back(std::vector<int> {i, 0});
                }

                continue;
            }
            if (interval[0] == 0 && interval[1] == height - 1)
            {
                if (inverted == Level::CROSS)
                    hidden_fill_cols.push_back(std::vector<int> {i, j});
                else
                    hidden_cross_cols.push_back(std::vector<int> {i, j});
            }

            if(col_find(i, interval[0], interval[1] + 1, 
                            [&](int val){ return inverted == Level::FILLED && (val == -1 || (val % 2) == 0) 
                                  || inverted == Level::CROSS && (val % 2) != 0; }))
            {
                if (inverted == Level::FILLED)
                    hidden_fill_cols.push_back(std::vector<int> {i, j});
                else
                    hidden_cross_cols.push_back(std::vector<int> {i, j});
            }
            if(interval[0] > 0 && col_find(i, prev, interval[0],
                    [&](int val){ return inverted == Level::FILLED && (val % 2) != 0
                                  || inverted == Level::CROSS && (val == -1 || (val % 2) == 0); }))
            {
                buffer_cols.push_back({i, prev, interval[0] - 1});
            }

            prev = interval[1] + 1;
        }

        if (prev < height)
        {
            if (col_find(i, prev, height, 
                [&](int val){ return inverted == Level::FILLED && (val % 2) != 0
                                  || inverted == Level::CROSS && (val == -1 || (val % 2) == 0); }))
            {
                buffer_cols.push_back({i, prev, height - 1});
            }

        }
    }
}

void Logic_board::load_hidden_rows()
{
    for (std::vector<int> pos_interval : buffer_rows)
    {
        int x = pos_interval[0], left = pos_interval[1], right = pos_interval[2];
        int col = std::find(row_intervals[x].begin(), row_intervals[x].end(), std::vector<int> {left, right}) - row_intervals[x].begin();
        std::vector<int> res = {x, col};
        if (inverted == Level::FILLED)
            hidden_fill_rows.push_back(res);
        else
            hidden_cross_rows.push_back(res);
    }
    buffer_rows = {};
}

void Logic_board::load_hidden_cols()
{
    for (std::vector<int> pos_interval : buffer_cols)
    {
        int y = pos_interval[0], up = pos_interval[1], down = pos_interval[2];
        int row = std::find(col_intervals[y].begin(), col_intervals[y].end(), std::vector<int> {up, down}) - col_intervals[y].begin();
        std::vector<int> res = {y, row};
        if (inverted == Level::FILLED)
            hidden_fill_cols.push_back(res);
        else
            hidden_cross_cols.push_back(res);
    }
    buffer_cols = {};
}

std::vector<int> Logic_board::row_changed(int x, int y, int needful_value, int opposed_value, Level::Needful state)
{
    std::vector<int> res {};

    if (current[x][y] % 2 != needful_value) return res;

    int left = y, right = y;
    while (true)
    {
        if ((left == 0 || left > 0 && (current[x][left - 1] < 0 || current[x][left - 1] % 2 == opposed_value)) &&
            (right == width - 1 || right < width - 1 && (current[x][right + 1] < 0 || current[x][right + 1] % 2 == opposed_value)))
            break;
        if (left > 0 && current[x][left - 1] >= 0 && current[x][left - 1] % 2 == needful_value && current[x][left - 1] != -1)
            --left;
        if (right < width - 1 && current[x][right + 1] >= 0 && current[x][right + 1] % 2 == needful_value && current[x][right + 1] != -1)
            ++right;
    }

    if ((left == 0 || left > 0 && correct[x][left - 1] % 2 == opposed_value) && 
        (right == width - 1 || right < width - 1 && correct[x][right + 1] % 2 == opposed_value))
    {
        int col = 0;
        if (state == inverted)
        {
            col = std::find(row_intervals[x].begin(), row_intervals[x].end(), std::vector<int> {left, right}) - row_intervals[x].begin();
            res = {x, col};
            if (state == Level::FILLED)
                hidden_fill_rows.push_back(res);
            else
                hidden_cross_rows.push_back(res);
        }
        else
        {
            buffer_rows.push_back({x, left, right});
        }
    }
    return res;
}

std::vector<int> Logic_board::col_changed(int x, int y, int needful_value, int opposed_value, Level::Needful state)
{
    std::vector<int> res {};

    if (current[x][y] % 2 != needful_value) return res;

    int down = x, up = x;
    while (true)
    {
        if ((up == 0 || up > 0 && (current[up - 1][y] < 0 || current[up - 1][y] % 2 == opposed_value)) &&
            (down == height - 1 || down < height - 1 && (current[down + 1][y] < 0 || current[down + 1][y] % 2 == opposed_value)))
            break;
        if (up > 0 && current[up - 1][y] >= 0 && current[up - 1][y] % 2 == needful_value && current[up - 1][y] != -1)
            --up;
        if (down < height - 1 && current[down + 1][y] >= 0 && current[down + 1][y] % 2 == needful_value && current[down + 1][y] != -1)
            ++down;
    }

    if ((up == 0 || up > 0 && correct[up - 1][y] % 2 == opposed_value) && 
        (down == height - 1 || down < height - 1 && correct[down + 1][y] % 2 == opposed_value))
    {
        if (state == inverted)
        {
            int row = std::find(col_intervals[y].begin(), col_intervals[y].end(), std::vector<int> {up, down}) - col_intervals[y].begin();
            res = {y, row};
            if (state == Level::FILLED)
                hidden_fill_cols.push_back(res);
            else
                hidden_cross_cols.push_back(res);
        }
        else
        {
            buffer_cols.push_back({y, up, down});
        }
    }

    return res;
}

std::vector<std::vector<int>> Logic_board::changed_digits(int x, int y, Level::Needful state)
{
    int needful_value = (state == Level::FILLED ? 1 : 0);
    int opposed_value = (state == Level::FILLED ? 0 : 1);

    std::vector<std::vector<int>> res (2, std::vector<int> {});
    if (current[x][y] < 0 || current[x][y] % 2 == opposed_value) return res;

    res[0] = row_changed(x, y, needful_value, opposed_value, state);
    res[1] = col_changed(x, y, needful_value, opposed_value, state);

    return res;
}

void Logic_board::set_click(int x, int y, int val)
{
    if (current[x][y] == -1)
    {
        current[x][y] = val;
        empty.erase(std::find(empty.begin(), 
                    empty.end(), std::vector<int> {x, y}));
        if (correct[x][y] == 1) ++correct_count;
    }
    status = (correct_count == finish_count ? FINISH : (current[x][y] == correct[x][y] ? OK : MISTAKE));
    if (status == MISTAKE)
        current[x][y] = correct[x][y] + 4;
}

std::vector<int> Logic_board::hint_click()
{
    if (correct_count == finish_count) 
        return std::vector<int> {};
    
    int rand_ind = std::rand() % empty.size();
    std::vector<int> pos = empty[rand_ind];
    int x = pos[0];
    int y = pos[1];
    current[x][y] = correct[x][y] + 2;

    empty.erase(empty.begin() + rand_ind);
    if (correct[x][y] == 1)
        ++correct_count;
    status = (correct_count == finish_count ? FINISH : OK);

    return pos;
}

void Logic_board::after_hint(std::vector<int> position)
{
    current[position[0]][position[1]] -= 2;
}

void Logic_board::after_mistake(std::vector<int> position)
{
    current[position[0]][position[1]] -= 4;
}