#ifndef DATABASE.H
#define DATABASE .H

#include <string>
#include <vector>
#include <iostream>

#include "sqlite3/sqlite3.h"

struct Level
{
    std::string title{};
    std::string size{};
    std::vector<std::vector<int>> correct_values{};
    std::vector<std::vector<int>> current_values{};
    int hearts_count = 3;
    bool finished = false;
};

struct Database_levels
{
public:
    enum class Response
    {
        OK,
        ALREADY_EXISTS,
        FAIL
    };

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

    Level get_level(const std::string &title, const std::string &size);

    int get_new_id(const std::string &size);

private:
    sqlite3 *db;

    static int new_id(void *id, int count, char **values, char **cols);

    static int select_level(void *l, int count, char **values, char **cols);

    static int check_exists(void *r, int counts, char **values, char **cols);

    std::string vector_to_string(std::vector<std::vector<int>> &vec);

    static std::vector<std::vector<int>> string_to_vector(const std::string &str);
};

#endif // DATABASE.H