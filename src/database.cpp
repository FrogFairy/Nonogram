#include <sstream>

#include "database.h"

Database_levels::Response Database_levels::add_level(Level& level)
{
    char* err = nullptr;
    Response response = Response::OK;
    std::string sql_check = "SELECT title, size FROM levels WHERE title = '" + level.title + "' AND size = '" + to_string(level.size) + "'";
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
    
    std::string finish = level.finished ? "1" : "0";
    std::string sql = "INSERT INTO levels (title, size, correct_values, current_values, empty, hearts_count, finished, inverted) " \
                    "VALUES ('" + level.title + "', '" + to_string(level.size) + "', '" +
                    vector_to_string(enum_to_vec(level._correct_values)) + 
                    "', '" + vector_to_string(enum_to_vec(level._current_values)) +
                    "', '" + positions_to_string(level._empty) + "', '" + std::to_string(level.hearts_count) +
                    "', '" + finish + "', '" + std::to_string(level.inverted) + "')";
    int res = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error add level: " << err << std::endl;
        sqlite3_free(err);
        return Response::FAIL;
    }
    return Response::OK;
}

Level Database_levels::get_level(Size size, const std::string& title)
{
    char* err = nullptr;
    std::vector<Level> level{};
    std::string sql = "SELECT title, size, correct_values, current_values, empty, hearts_count, finished, inverted " \
                        "FROM levels WHERE size = '" + to_string(size) + "' AND title = '" + title + "'";
    int rs = sqlite3_exec(db, sql.c_str(), select_levels, &level, &err);
    if (rs != SQLITE_OK)
    {
        std::cerr << "Error select title and size from table: " << err << std::endl;
        sqlite3_free(err);
        return level[0];
    }
    return level[0];
}

std::vector<Level> Database_levels::get_levels(Size size)
{
    char* err = nullptr;
    std::vector<Level> levels{};
    std::string sql = "SELECT title, size, correct_values, current_values, empty, hearts_count, finished, inverted " \
                            "FROM levels WHERE size = '" + to_string(size) + "'";
    int rs = sqlite3_exec(db, sql.c_str(), select_levels, &levels, &err);
    if (rs != SQLITE_OK)
    {
        std::cerr << "Error select title and size from table: " << err << std::endl;
        sqlite3_free(err);
        return std::vector<Level> {};
    }
    return levels;
}

Database_levels::Response Database_levels::update_level(Level& level)
{
    char* err = nullptr;
    Response response = Response::OK;
    std::string finish = level.finished ? "1" : "0";
    std::string sql = "UPDATE levels SET correct_values = '" + vector_to_string(enum_to_vec(level._correct_values)) + 
                      "', current_values = '" + vector_to_string(enum_to_vec(level._current_values)) +
                      "', empty = '" + positions_to_string(level._empty) + 
                      "', hearts_count = '" + std::to_string(level.hearts_count) + 
                      "', finished = '" + finish + "', inverted = '" + std::to_string(level.inverted) +
                      "' WHERE size = '" + to_string(level.size) +
                      "' AND title = '" + level.title + "'";
    int res = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error update_finished level: " << err << std::endl;
        sqlite3_free(err);
        return Response::FAIL;
    }
    return Response::OK;
}

Database_levels::Response Database_levels::update_current(Level& level)
{
    char* err = nullptr;
    Response response = Response::OK;
    std::string sql = "UPDATE levels SET current_values = '" + vector_to_string(enum_to_vec(level._current_values)) +
                      "', empty = '" + positions_to_string(level._empty) + "' WHERE size = '" + to_string(level.size) + 
                      "' AND title = '" + level.title + "'";
    int res = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error update_current level: " << err << std::endl;
        sqlite3_free(err);
        return Response::FAIL;
    }
    return Response::OK;
}

Database_levels::Response Database_levels::update_finished(Level& level)
{
    char* err = nullptr;
    Response response = Response::OK;
    std::string finish = level.finished ? "1" : "0";
    std::string sql = "UPDATE levels SET finished = '" + finish + "' WHERE size = '" + to_string(level.size) +
                      "' AND title = '" + level.title + "'";
    int res = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error update_finished level: " << err << std::endl;
        sqlite3_free(err);
        return Response::FAIL;
    }
    return Response::OK;
}

Database_levels::Response Database_levels::update_inverted(Level& level)
{
    char* err = nullptr;
    Response response = Response::OK;
    std::string sql = "UPDATE levels SET inverted = '" + std::to_string(level.inverted) +
                      "' WHERE size = '" + to_string(level.size) +
                      "' AND title = '" + level.title + "'";
    int res = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error update_inverted level: " << err << std::endl;
        sqlite3_free(err);
        return Response::FAIL;
    }
    return Response::OK;
}

Database_levels::Response Database_levels::update_heart_count(Level& level)
{
    char* err = nullptr;
    Response response = Response::OK;
    std::string sql = "UPDATE levels SET hearts_count = '" + std::to_string(level.hearts_count) + "' WHERE size = '" + to_string(level.size) +
                      "' AND title = '" + level.title + "'";
    int res = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error update_finished level: " << err << std::endl;
        sqlite3_free(err);
        return Response::FAIL;
    }
    return Response::OK;
}

int Database_levels::get_new_id(Size size)
{
    char* err = nullptr;
    int id = 1;
    std::string sql_check = "SELECT size FROM levels WHERE size = '" + to_string(size) + "'";
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
        level.size = size_to_int(values[1]);
        level._correct_values = vec_to_enum(string_to_vector(values[2]), Level::Needful::FILLED_VAL);
        level._current_values = vec_to_enum(string_to_vector(values[3]), Level::Cell_state::FILLED);
        level._empty = string_to_positions(values[4]);
        level.hearts_count = std::atoi(values[5]);
        level.finished = std::atoi(values[6]);
        level.inverted = Level::Needful(std::atoi(values[7]));
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

std::string Database_levels::vector_to_string(std::vector<std::vector<int>> vec) const
{
    std::string res = "";
    for (size_t y = 0; y < vec.size(); ++y)
    {
        for (size_t x = 0; x < vec[y].size(); ++x)
        {
            res += std::to_string(vec[y][x]);
            if (x != vec[y].size() - 1) res += " ";
        }
        if (y != vec.size() - 1) res += "\n";
    }
    return res;
}

std::string Database_levels::positions_to_string(std::vector<Position>& vec) const
{
    std::string res = "";
    for (size_t y = 0; y < vec.size(); ++y)
    {
        res += std::to_string(vec[y].x) + " " + std::to_string(vec[y].x) + "\n";
    }
    return res;
}

std::vector<std::vector<int>> Database_levels::string_to_vector(const std::string& str)
{
    std::vector<std::vector<int>> res {};
    if (str.length() == 0) return res;
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

std::vector<Position> Database_levels::string_to_positions(const std::string& str)
{
    std::vector<Position> res {};
    if (str.length() == 0) return res;
    std::stringstream lines(str);
    std::string line;
    std::stringstream digits;
    int i = 0;
    while(std::getline(lines, line))
    {
        digits = std::stringstream(line);
        int x, y;
        digits >> x;
        digits >> y;
        res.push_back(Position {x, y});
        ++i;
    }
    return res;
}

template<LevelConcept T>
std::vector<std::vector<int>> Database_levels::enum_to_vec(std::vector<std::vector<T>>& vec) const
{
    std::vector<std::vector<int>> res {vec.size()};
    for (int i = 0; i < vec.size(); ++i)
    {
        for (int j = 0; j < vec[i].size(); ++j)
        {
            res[i].push_back(int(vec[i][j]));
        }
    }
    return res;
}

template<LevelConcept T>
std::vector<std::vector<T>> Database_levels::vec_to_enum(std::vector<std::vector<int>> vec, T val)
{
    std::vector<std::vector<T>> res {vec.size()};
    for (int i = 0; i < vec.size(); ++i)
    {
        for (int j = 0; j < vec[i].size(); ++j)
        {
            res[i].push_back(T(vec[i][j]));
        }
    }
    return res;
}