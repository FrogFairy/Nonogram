#ifndef BOARDF_H
#define BOARDF_H
#include <iostream>
#include <vector>
#include <random>
#include <string>

bool check_click(std::vector<std::vector<int>> current, std::vector<std::vector<int>> correct)
{
 for(size_t i{0}; i < correct.size(); ++i )
 {
    for(size_t j{0}; j < correct[i].size(); ++j )
    {
        if (( current[i][j] != -1 && current[i][j] != correct[i][j]))
        {
           current[i][j] =  correct[i][j];
           return false;
        }
    }
 }
 return true;
}


std::string hint_click(std::vector<std::vector<int>> current, std::vector<std::vector<int>> correct)
{
    int randnum = rand()%(current.size() * current[0].size() - 1) +1;
    
    while (randnum > 0)
    {
        for(size_t i{0}; i < correct.size(); ++i )
        {
            for(size_t j{0}; j < correct[i].size(); ++j )
            {
                if(current[i][j] == -1)
                {
                    randnum -= 1;
                    if (randnum == 0) 
                    {
                        current[i][j] = correct[i][j] + 2;
                        return std::to_string(i) + " " + std::to_string(j);
                    }

                }
            }
        }
    }
    throw "Something went wrong";
}

void after_hint(std::vector<std::vector<int>> current, std::string position)
{
    size_t delimit = position.find(" ");
    int i = stoi(position);
    int j = stoi(position, &delimit);
    current[i][j] -= 2;
    
}
#endif //BOARDF_H
