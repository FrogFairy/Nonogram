#include <iostream>
#include <sstream>

#include "database.h"

Database_levels::Response Database_levels::add_level(Level level)
{
    char* err;
    Response response;
    std::string sql_check = "SELECT title, size FROM levels WHERE title == '" + level.title + "' AND size == '" + level.size + "'";
    int rs = sqlite3_exec(db, sql_check.c_str(), check_exists, &response, &err);
    if (rs != SQLITE_OK)
    {
        std::cerr << "Error select title from table: " << err << std::endl;
        sqlite3_free(err);
        return Response::FAIL;
    }
    if (response != Response::OK)
    {
        return response;
    }

    std::string sql = "INSERT INTO levels (title, size, correct_values) "
                    "VALUES ('" + level.title + "', '" + level.size + "', '" +
                    vector_to_string(level.correct_values) + "')";
    int res = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error add level: " << err << std::endl;
        sqlite3_free(err);
        return Response::FAIL;
    }
    return Response::OK;
}

Level Database_levels::get_level(const std::string& title, const std::string& size)
{
    char* err;
    Level level;
    std::string sql_check = "SELECT title, size, correct_values, current_values, hearts_count, finished "
                            "FROM levels WHERE title == '" + title + "' AND size == '" + size + "'";
    int rs = sqlite3_exec(db, sql_check.c_str(), select_level, &level, &err);
    if (rs != SQLITE_OK)
    {
        std::cerr << "Error select title and size from table: " << err << std::endl;
        sqlite3_free(err);
        return Level{};
    }
    return level;
}

int Database_levels::get_new_id(const std::string& size)
{
    char* err;
    int id;
    std::string sql_check = "SELECT size FROM levels WHERE size == '" + size + "'";
    int rs = sqlite3_exec(db, sql_check.c_str(), new_id, &id, &err);
    if (rs != SQLITE_OK)
    {
        std::cerr << "Error select size from table: " << err << std::endl;
        sqlite3_free(err);
        return 0;
    }
    return id;
}

int Database_levels::new_id(void * id, int count, char **values, char **cols)
{
    int* res = static_cast<int*>(id);
    *res = count + 1;
    return 0;
}

int Database_levels::select_level(void * l, int count, char **values, char **cols)
{
    Level* res = static_cast<Level*>(l);
    *res = Level{};
    if (count)
    {
        res->title = values[0];
        res->size = values[1];
        res->correct_values = string_to_vector(values[2]);
        res->current_values = string_to_vector(values[3]);
        res->hearts_count = std::atoi(values[4]);
        res->finished = std::atoi(values[5]);
    }
    return 0;
}

int Database_levels::check_exists(void * r, int counts, char **values, char **cols)
{
    Response* res = static_cast<Response*>(r);
    if (counts) *res = Response::ALREADY_EXISTS;
    else *res = Response::OK;
    return 0;
}

std::string Database_levels::vector_to_string(std::vector<std::vector<int>>& vec)
{
    std::string res = "";
    for (size_t y = 0; y < vec.size(); ++y)
    {
        for (size_t x = 0; x < vec.size(); ++x)
        {
            res += std::to_string(vec[y][x]);
            if (x != vec.size() - 1) res += " ";
        }
        if (y != vec.size() - 1) res += "\n";
    }
    return res;
}

std::vector<std::vector<int>> Database_levels::string_to_vector(const std::string& str)
{
    if (str.length() == 0) return std::vector<std::vector<int>>{};
    std::vector<std::vector<int>> res;
    std::stringstream lines(str);
    std::string line;
    std::stringstream digits;
    int symb;
    int i = 0;
    while(std::getline(lines, line))
    {
        digits = std::stringstream(line);
        res.push_back(std::vector<int> {});
        while(digits >> symb)
        {
            res[i].push_back(symb);
        }
        ++i;
    }
    return res;
}