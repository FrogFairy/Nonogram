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
    Level(const std::string& title, const std::string& size, const std::string& filename)
        : title{title}, size{size}, filename{filename}
    {
        std::vector<int> s = size_to_int(size);
        correct_values = create_matrix_level(s[0], s[1], filename);
    }

    void restart()
    {
        current_values = std::vector<std::vector<int>> {};
        empty = std::vector<std::vector<int>> {};
        hidden_rows = empty_rows;
        hidden_cols = empty_cols;
        hearts_count = 3;
        finished = false;
        init();
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
    
    void set_current(std::vector<std::vector<int>>& current, std::vector<std::vector<int>>& empty) 
    { 
        this->current_values = current;
        this->empty = empty;
    }

    void set_hearts(int hearts) { hearts_count = hearts; }
    void set_finished(bool finish) { finished = finish; }
    
    std::string title{};
    std::string size{};
    std::vector<std::vector<int>> correct_values{};
    std::vector<std::vector<int>> current_values{};
    std::vector<std::vector<int>> empty{};
    std::vector<std::vector<int>> hidden_rows{};
    std::vector<std::vector<int>> hidden_cols{};
    int hearts_count = 3;
    bool finished = false;

    std::vector<std::vector<int>> empty_rows {}; // for coord 0 digits in rows
    std::vector<std::vector<int>> empty_cols {}; // for coord 0 digits in cols

    std::string filename;
};

struct Database_levels
{
public:
    enum Response {OK, ALREADY_EXISTS, FAIL};

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

    Response add_level(Level& level);

    Level get_level(const std::string& size, const std::string& title);
    std::vector<Level> get_levels(const std::string& size);

    Response update_level(Level& level);
    Response update_current(Level& level);
    Response update_finished(Level& level);
    Response update_heart_count(Level& level);
    Response update_hidden_rows(Level& level);
    Response update_hidden_cols(Level& level);

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