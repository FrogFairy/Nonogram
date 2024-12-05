#include "logic_board.h"

#include <random>
#include <algorithm>

bool Logic_board::set_click(int x, int y, int val)
{
    if (current[x][y] == -1)
    {
        current[x][y] = val;
        empty.erase(std::find(empty.begin(), 
                    empty.end(), std::vector<int> {x, y}));
        if (current[x][y] == correct[x][y]) ++correct_count;
    }
    return current[x][y] == correct[x][y];
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
    ++correct_count;

    return pos;
}

void Logic_board::after_hint(std::vector<int> position)
{
    current[position[0]][position[1]] -= 2;
}