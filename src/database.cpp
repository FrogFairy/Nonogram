#include <sstream>

#include "database.h"

std::vector<int> size_to_int(const std::string& size)
{
    int w = std::stoi(size.substr(0, size.find("x")));
    int h = std::stoi(size.substr(size.find("x" + 1)));
    return std::vector<int> {w, h};
}

Database_levels::Response Database_levels::add_level(Level level)
{
    char* err;
    Response response = Response::OK;
    std::string sql_check = "SELECT title, size FROM levels WHERE title = '" + level.title + "' AND size = '" + level.size + "'";
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

    std::string sql = "INSERT INTO levels (title, size, correct_values, current_values, empty) "
                    "VALUES ('" + level.title + "', '" + level.size + "', '" +
                    vector_to_string(level.correct_values) + "', '" + vector_to_string(level.current_values) +
                    "', '" + vector_to_string(level.empty) + "')";
    int res = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error add level: " << err << std::endl;
        sqlite3_free(err);
        return Response::FAIL;
    }
    return Response::OK;
}

Level Database_levels::get_level(const std::string& size, const std::string& title)
{
    char* err;
    std::vector<Level> level{};
    std::string sql = "SELECT title, size, correct_values, current_values, empty, hearts_count, finished "
                            "FROM levels WHERE size = '" + size + "' AND title = '" + title + "'";
    int rs = sqlite3_exec(db, sql.c_str(), select_levels, &level, &err);
    if (rs != SQLITE_OK)
    {
        std::cerr << "Error select title and size from table: " << err << std::endl;
        sqlite3_free(err);
        return level[0];
    }
    return level[0];
}

std::vector<Level> Database_levels::get_levels(const std::string& size)
{
    char* err;
    std::vector<Level> levels{};
    std::string sql = "SELECT title, size, correct_values, current_values, empty, hearts_count, finished "
                            "FROM levels WHERE size = '" + size + "'";
    int rs = sqlite3_exec(db, sql.c_str(), select_levels, &levels, &err);
    if (rs != SQLITE_OK)
    {
        std::cerr << "Error select title and size from table: " << err << std::endl;
        sqlite3_free(err);
        return std::vector<Level> {};
    }
    return levels;
}

int Database_levels::get_new_id(const std::string& size)
{
    char* err;
    int id = 1;
    std::string sql_check = "SELECT size FROM levels WHERE size = '" + size + "'";
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
    (*(int*) id)++;
    return 0;
}

int Database_levels::select_levels(void * l, int count, char **values, char **cols)
{
    Level level {};
    if (count)
    {
        level.title = values[0];
        level.size = values[1];
        level.correct_values = string_to_vector(values[2]);
        level.current_values = string_to_vector(values[3]);
        level.empty = string_to_vector(values[4]);
        level.hearts_count = std::atoi(values[5]);
        level.finished = std::atoi(values[6]);
    }
    (*(std::vector<Level>*) l).push_back(level);
    return 0;
}

int Database_levels::check_exists(void * r, int counts, char **values, char **cols)
{
    if (counts) (*(Response*) r) = Response::ALREADY_EXISTS;
    else (*(Response*) r) = Response::OK;
    return 0;
}

std::string Database_levels::vector_to_string(std::vector<std::vector<int>>& vec)
{
    std::string res = "";
    for (size_t y = 0; y < vec.size(); ++y)
    {
        for (size_t x = 0; x < vec[0].size(); ++x)
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