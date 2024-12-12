#include "logic_board.h"

#include <random>
#include <algorithm>

void Logic_board::fill_row_digits()
{
    for (int i = 0; i < correct.size(); ++i)
    {
        std::vector<std::vector<int>> intervals {};
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
    for (int i = 0; i < correct[0].size(); ++i)
    {
        std::vector<std::vector<int>> intervals {};
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

std::vector<int> Logic_board::row_changed(int x, int y)
{
    std::vector<int> res {};

    int left = y, right = y;
    while (true)
    {
        if ((left == 0 || left > 0 && (current[x][left - 1] < 0 || current[x][left - 1] % 2 == 0)) &&
            (right == width - 1 || right < width - 1 && (current[x][right + 1] < 0 || current[x][right + 1] % 2 == 0)))
            break;
        if (left > 0 && current[x][left - 1] > 0 && current[x][left - 1] % 2 != 0)
            --left;
        if (right < width - 1 && current[x][right + 1] > 0 && current[x][right + 1] % 2 != 0)
            ++right;
    }

    if ((left == 0 || left > 0 && correct[x][left - 1] % 2 == 0) && 
        (right == width - 1 || right < width - 1 && correct[x][right + 1] % 2 == 0))
    {
        int col = std::find(row_intervals[x].begin(), row_intervals[x].end(), std::vector<int> {left, right}) - row_intervals[x].begin();
        res = {x, col};
    }
    return res;
}

std::vector<int> Logic_board::col_changed(int x, int y)
{
    std::vector<int> res {};

    int down = x, up = x;
    while (true)
    {
        if ((up == 0 || up > 0 && (current[up - 1][y] < 0 || current[up - 1][y] % 2 == 0)) &&
            (down == height - 1 || down < height - 1 && (current[down + 1][y] < 0 || current[down + 1][y] % 2 == 0)))
            break;
        if (up > 0 && current[up - 1][y] > 0 && current[up - 1][y] % 2 != 0)
            --up;
        if (down < height - 1 && current[down + 1][y] > 0 && current[down + 1][y] % 2 != 0)
            ++down;
    }

    if ((up == 0 || up > 0 && correct[up - 1][y] % 2 == 0) && 
        (down == height - 1 || down < height - 1 && correct[down + 1][y] % 2 == 0))
    {
        int row = std::find(col_intervals[y].begin(), col_intervals[y].end(), std::vector<int> {up, down}) - col_intervals[y].begin();
        res = {y, row};
    }

    return res;
}

std::vector<std::vector<int>> Logic_board::changed_digits(int x, int y)
{
    std::vector<std::vector<int>> res (2, std::vector<int> {});
    if (current[x][y] < 0 || current[x][y] % 2 == 0) return res;

    res[0] = row_changed(x, y);
    res[1] = col_changed(x, y);

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
    if (correct_count == current.size() * current[0].size()) 
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