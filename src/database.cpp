#include <sstream>

#include "database.h"

Size size_to_int(const std::string& size)
{
    int w = std::stoi(size.substr(0, size.find("x")));
    int h = std::stoi(size.substr(size.find("x") + 1));
    return Size(w, h);
}

Database_levels::Response Database_levels::add_level(Level& level)
{
    char* err = nullptr;
    Response response = Response::OK;
    std::string sql_check = "SELECT title, size FROM levels WHERE title = '" + level._title + "' AND size = '" + to_string(level._size) + "'";
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
    std::string sql = "INSERT INTO levels (title, size, correct_values, current_values, empty, hidden_rows, hidden_cols, empty_rows, empty_cols, hearts_count, finished) "
                    "VALUES ('" + level.title + "', '" + to_string(level.size) + "', '" +
                    vector_to_string(level.correct_values) + "', '" + vector_to_string(level.current_values) +
                    "', '" + vector_to_string(level.empty) + "', '" + vector_to_string(level.empty_rows) + 
                    "', '" + vector_to_string(level.empty_cols) +
                    "', '" + vector_to_string(level.empty_rows) + 
                    "', '" + vector_to_string(level.empty_cols) + "', '"
                    + std::to_string(level.hearts_count) +
                    "', '" + finish + "')";
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
    std::string sql = "SELECT title, size, correct_values, current_values, empty, hidden_rows, hidden_cols, empty_rows, empty_cols, hearts_count, finished "
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
    std::string sql = "SELECT title, size, correct_values, current_values, empty, hidden_rows, hidden_cols, empty_rows, empty_cols, hearts_count, finished "
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
    std::string sql = "UPDATE levels SET correct_values = '" + vector_to_string(level.correct_values) + 
                      "', current_values = '" + vector_to_string(level.current_values) +
                      "', empty = '" + vector_to_string(level.empty) + 
                      "', hidden_rows = '" + vector_to_string(level.hidden_rows) +
                      "', hidden_cols = '" + vector_to_string(level.hidden_cols) +
                      "', hearts_count = '" + std::to_string(level.hearts_count) + 
                      "', finished = '" + finish + "' WHERE size = '" + to_string(level.size) +
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
    std::string sql = "UPDATE levels SET current_values = '" + vector_to_string(level.current_values) +
                      "', empty = '" + vector_to_string(level.empty) + "' WHERE size = '" + to_string(level.size) + 
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

Database_levels::Response Database_levels::update_hidden_rows(Level& level)
{
    char* err = nullptr;
    Response response = Response::OK;
    std::string sql = "UPDATE levels SET hidden_rows = '" + vector_to_string(level.hidden_rows) + "' WHERE size = '" + to_string(level.size) +
                      "' AND title = '" + level.title + "'";
    int res = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error update_hidden_rows level: " << err << std::endl;
        sqlite3_free(err);
        return Response::FAIL;
    }
    return Response::OK;
}

Database_levels::Response Database_levels::update_hidden_cols(Level& level)
{
    char* err = nullptr;
    Response response = Response::OK;
    std::string sql = "UPDATE levels SET hidden_cols = '" + vector_to_string(level.hidden_cols) + "' WHERE size = '" + to_string(level.size) +
                      "' AND title = '" + level.title + "'";
    int res = sqlite3_exec(db, sql.c_str(), 0, 0, &err);
    if (res != SQLITE_OK)
    {
        std::cerr << "Error update_hidden_cols level: " << err << std::endl;
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
        level.correct_values = string_to_vector(values[2]);
        level.current_values = string_to_vector(values[3]);
        level.empty = string_to_vector(values[4]);
        level.hidden_rows = string_to_vector(values[5]);
        level.hidden_cols = string_to_vector(values[6]);
        level.empty_rows = string_to_vector(values[7]);
        level.empty_cols = string_to_vector(values[8]);
        level.hearts_count = std::atoi(values[9]);
        level.finished = std::atoi(values[10]);
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
        for (size_t x = 0; x < vec[y].size(); ++x)
        {
            res += std::to_string(vec[y][x]);
            if (x != vec[y].size() - 1) res += " ";
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