#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3/sqlite3.h"
#include "create_level.h"

#include <string>
#include <vector>
#include <iostream>

std::vector<int> size_to_int(const std::string& size);

struct Level
{
    Level() = default;
    Level(const std::string& title, const std::string size, const std::string filename)
        : title{title}, size{size}
    {
        std::vector<int> s = size_to_int(size);
        correct_values = create_matrix_level(s[0], s[1], filename);
    }
    
    void init()
    {
        for (int j = 0; j < correct_values.size(); ++j)
        {
            for (int i = 0; i < correct_values[0].size(); ++i)
            {
                empty.push_back(std::vector<int> {j, i});
            }
            current_values.push_back(std::vector<int>(correct_values[0].size(), -1));
        }
    }
    
    std::string title{};
    std::string size{};
    std::vector<std::vector<int>> correct_values{};
    std::vector<std::vector<int>> current_values{};
    std::vector<std::vector<int>> empty{};
    int hearts_count = 3;
    bool finished = false;
};

struct Database_levels
{
public:
    enum class Response {OK, ALREADY_EXISTS, FAIL};

    Database_levels()
    {
        int cursor = sqlite3_open("../db/nonogram.db", &db);
        if (cursor)
            std::cerr << "can`t open database" << std::endl;
    }

    ~Database_levels()
    {
        sqlite3_close(db);
    }

    Response add_level(Level level);
    Level get_level(const std::string& size, const std::string& title);
    std::vector<Level> get_levels(const std::string& size);

    int get_new_id(const std::string& size);

private:
    sqlite3* db;

    static int new_id(void * id, int count, char **values, char **cols);

    static int select_levels(void * l, int count, char **values, char **cols);

    static int check_exists(void * r, int counts, char **values, char **cols);

    std::string vector_to_string(std::vector<std::vector<int>>& vec);

    static std::vector<std::vector<int>> string_to_vector(const std::string& str);
};

#endif // DATABASE_H