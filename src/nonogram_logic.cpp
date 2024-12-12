#include "nonogram_logic.h"

#include <random>
#include <algorithm>

void Nonogram_logic::fill_row_digits() 
{
    for (int i = 0; i < correct.size(); ++i)
    {
        std::vector<Position> intervals {};
        int start = -1;
        for (int j = 0; j < correct[0].size(); ++j)
        {
            if (correct[i][j] == 1)
            {
                if (start < 0)
                    start = j;
                ++finish_count;
            }
            if (start >= 0 && (correct[i][j] == 0 || j == correct[0].size() - 1))
            {
                if (correct[i][j] == 0)
                    intervals.push_back(Position {start, j - 1});
                else 
                    intervals.push_back(Position {start, j});
                start = -1;
            }
            if (current[i][j] == 1) ++correct_count;
        }
        if (!intervals.size())
        {
            intervals.push_back(Position{0,0});
        }
        row_intervals.push_back(intervals);
        max_rows = std::max(max_rows, (int) intervals.size());
    }
}

void Nonogram_logic::fill_col_digits()
{
    for (int i = 0; i < correct[0].size(); ++i)
    {
        std::vector<Position> intervals {};
        int end = -1;
        for (int j = correct.size() - 1; j >= 0; --j)
        {
            if (correct[j][i] == 1)
            {
                if (end < 0)
                    end = j;
            }
            if (end >= 0 && (correct[j][i] == 0 || j == 0))
            {
                if (correct[j][i] == 0)
                    intervals.push_back(Position {j + 1, end});
                else 
                    intervals.push_back(Position {j, end});
                end = -1;
            }
        }
        if (!intervals.size())
        {
            intervals.push_back(Position {0,0});
        }
        col_intervals.push_back(intervals);
        max_cols = std::max(max_cols, (int) intervals.size());
    }  
}

Position Nonogram_logic::row_changed(Position pos)
{
    Position res {};

    int left = pos.y, right = pos.y;
    while (true)
    {
        if ((left == 0 || left > 0 && (current[pos.x][left - 1] < 0 || current[pos.x][left - 1] % 2 == 0)) &&
            (right == width - 1 || right < width - 1 && (current[pos.x][right + 1] < 0 || current[pos.x][right + 1] % 2 == 0)))
            break;
        if (left > 0 && current[pos.x][left - 1] > 0 && current[pos.x][left - 1] % 2 != 0)
            --left;
        if (right < width - 1 && current[pos.x][right + 1] > 0 && current[pos.x][right + 1] % 2 != 0)
            ++right;
    }

    if ((left == 0 || left > 0 && correct[pos.x][left - 1] % 2 == 0) && 
        (right == width - 1 || right < width - 1 && correct[pos.x][right + 1] % 2 == 0))
    {
        int col = std::find(row_intervals[pos.x].begin(), row_intervals[pos.x].end(), Position {left, right}) - row_intervals[pos.x].begin();
        res {pos.x, col};
    }
    return res;
}

Position Nonogram_logic::col_changed(Position pos)
{
    Position res {};

    int down = pos.x, up = pos.x;
    while (true)
    {
        if ((up == 0 || up > 0 && (current[up - 1][pos.y] < 0 || current[up - 1][pos.y] % 2 == 0)) &&
            (down == height - 1 || down < height - 1 && (current[down + 1][pos.y] < 0 || current[down + 1][pos.y] % 2 == 0)))
            break;
        if (up > 0 && current[up - 1][pos.y] > 0 && current[up - 1][pos.y] % 2 != 0)
            --up;
        if (down < height - 1 && current[down + 1][pos.y] > 0 && current[down + 1][pos.y] % 2 != 0)
            ++down;
    }

    if ((up == 0 || up > 0 && correct[up - 1][pos.y] % 2 == 0) && 
        (down == height - 1 || down < height - 1 && correct[down + 1][pos.y] % 2 == 0))
    {
        int row = std::find(col_intervals[pos.y].begin(), col_intervals[pos.y].end(), Position {up, down}) - col_intervals[pos.y].begin();
        res {pos.y, row};
    }

    return res;
}

std::vector<Position> Nonogram_logic::changed_digits(Position pos)
{
    std::vector<Position> res (2, Position {});
    if (current[pos.x][pos.y] < 0 || current[pos.x][pos.y] % 2 == 0) return res;

    res[0] = row_changed(Position{pos.x, pos.y});
    res[1] = col_changed(Position{pos.x, pos.y});

    return res;
}

void Nonogram_logic::set_cell(Position pos, int val)
{
    if (current[pos.x][pos.y] == -1)
    {
        current[pos.x][pos.y] = val;
        empty.erase(std::find(empty.begin(), 
                    empty.end(), std::vector<int> {pos.x, pos.y}));
        if (correct[pos.x][pos.y] == 1) ++correct_count;
    }
    status = (correct_count == finish_count ? FINISH : (current[pos.x][pos.y] == correct[pos.x][pos.y] ? OK : MISTAKE));
    if (status == MISTAKE)
        current[pos.x][pos.y] = correct[pos.x][pos.y] + 4;
}

Position Nonogram_logic::hint_click()
{
    if (correct_count == current.size() * current[0].size()) 
        return std::vector<int> {};
    
    int rand_ind = std::rand() % empty.size();
    Position pos {empty[rand_ind]};
    current[pos.x][pos.y] = correct[pos.x][pos.y] + 2;

    empty.erase(empty.begin() + rand_ind);
    if (correct[pos.x][pos.y] == 1)
        ++correct_count;
    status = (correct_count == finish_count ? FINISH : OK);

    return pos;
}

void Nonogram_logic::after_hint(Position pos)
{
    current[pos.x][pos.y] -= 2;
}

void Nonogram_logic::after_mistake(Position pos)
{
    current[pos.x][pos.y] -= 4;
}