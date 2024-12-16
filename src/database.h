#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite3/sqlite3.h"
#include "level.h"

#include <string>
#include <vector>
#include <iostream>
 
template<typename T>
concept LevelConcept = std::same_as<T, Level::Needful> || std::same_as<T, Level::Cell_state>;

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

    Level get_level(Size size, const std::string& title);
    std::vector<Level> get_levels(Size size);

    Response update_level(Level& level);
    Response update_current(Level& level);
    Response update_finished(Level& level);
    Response update_inverted(Level& level);
    Response update_heart_count(Level& level);

    int get_new_id(Size size);

private:
    sqlite3* db;

    static int new_id(void * id, int count, char **values, char **cols);

    static int select_levels(void * l, int count, char **values, char **cols);

    static int check_exists(void * r, int counts, char **values, char **cols);

    template<LevelConcept T>
    std::vector<std::vector<int>> enum_to_vec(std::vector<std::vector<T>>& vec) const;

    template<LevelConcept T>
    static std::vector<std::vector<T>> vec_to_enum(std::vector<std::vector<int>> vec, T val);

    std::string vector_to_string(std::vector<std::vector<int>> vec) const;
    std::string positions_to_string(std::vector<Position>& vec) const;

    static std::vector<std::vector<int>> string_to_vector(const std::string& str);
    static std::vector<Position> string_to_positions(const std::string& str);
};

#endif // DATABASE_H