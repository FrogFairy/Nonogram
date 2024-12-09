#include "logic_board.h"

#include <random>
#include <algorithm>

void Logic_board::fill_row_digits()
{
    for (int i = 0; i < correct.size(); ++i)
    {
        int rows_count = 0;
        std::vector<int> row {};
        for (int j = 0; j < correct[0].size(); ++j)
        {
            if (correct[i][j] == 1)
            {
                ++finish_count;
                ++rows_count;
            }
            if (rows_count && (correct[i][j] == 0 || j == correct[0].size() - 1))
            {
                row.push_back(rows_count);
                rows_count = 0;
            }
            if (current[i][j] == 1) ++correct_count;
        }
        if (!row.size()) row.push_back(0);
        row_digits.push_back(row);
        max_rows = std::max(max_rows, (int) row.size());
    }
}

void Logic_board::fill_col_digits()
{
    for (int i = 0; i < correct[0].size(); ++i)
    {
        int cols_count = 0;
        std::vector<int> col {};
        for (int j = correct.size() - 1; j >= 0; --j)
        {
            if (correct[j][i] == 1)
                ++cols_count;
            if (cols_count && (correct[j][i] == 0 || j == 0))
            {
                col.push_back(cols_count);
                cols_count = 0;
            }
        }
        if (!col.size()) col.push_back(0);
        col_digits.push_back(col);
        max_cols = std::max(max_cols, (int) col.size());
    }  
}

void Logic_board::set_click(int x, int y, int val)
{
    if (current[x][y] == -1)
    {
        current[x][y] = val;
        empty.erase(std::find(empty.begin(), 
                    empty.end(), std::vector<int> {x, y}));
        if (current[x][y] == correct[x][y] && correct[x][y] == 1) ++correct_count;
    }
    status = (current[x][y] == correct[x][y] ? (correct_count == finish_count ? FINISH : OK) : MISTAKE);
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