#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>

struct Size
{
    unsigned int width;
    unsigned int height;
};

struct Position
{
    bool empty() { return x < 0; }
    bool operator == (const Position& other) const
    {
        return other.x == x && other.y == y;
    }

    int x = -1;
    int y = -1;
};

struct Interval
{
    bool empty() { return start < 0; }
    bool operator == (const Interval& other) const
    {
        return other.start == start && other.end == end;
    }

    int start = -1;
    int end = -1;
};

struct Position_interval
{
    int pos = -1;
    Interval interval {};
};

std::string to_string(Size size);
Size size_to_int(const std::string& size);

struct Level
{
    friend class Database_levels;

    enum Needful
    {
        CROSS_VAL = 0,
        FILLED_VAL = 1
    };

    enum Cell_state
    {
        EMPTY = -1,
        CROSS = 0,
        FILLED = 1,
        HINT_CROSS = 2,
        HINT_FILLED = 3,
        MISTAKE_CROSS = 4,
        MISTAKE_FILLED = 5
    };

    Level() = default;
    Level(const std::string& title, Size size, const std::string& filename)
        : title{title}, size{size}
    {
        _correct_values = create_matrix_level(size, filename);
    }

    void restart()
    {
        _current_values = std::vector<std::vector<Cell_state>> {};
        _empty = std::vector<Position> {};
        hearts_count = 3;
        finished = false;
        init();
    }
    
    void init()
    {
        for (int j = 0; j < _correct_values.size(); ++j)
        {
            for (int i = 0; i < _correct_values[0].size(); ++i)
            {
                _empty.push_back(Position {j, i});
            }
            _current_values.push_back(std::vector<Cell_state>(_correct_values[0].size(), Cell_state::EMPTY));
        }
    }
    
    void set_current(std::vector<std::vector<Cell_state>> current, std::vector<Position> empty) 
    { 
        _current_values = current;
        _empty = empty;
    }

    std::vector<std::vector<Needful>> correct_values() { return _correct_values; }
    std::vector<std::vector<Cell_state>> current_values() { return _current_values; }
    std::vector<Position> get_empty() { return _empty; }

    std::string title{};
    Size size{};
    char hearts_count = 3;
    bool finished = false;
    Needful inverted = Needful::FILLED_VAL;

protected:    
    std::vector<std::vector<Needful>> _correct_values{};
    std::vector<std::vector<Cell_state>> _current_values{};
    std::vector<Position> _empty{}; // empty positions in user`s board

private:
    std::vector<std::vector<Needful>> create_matrix_level(Size size, const std::string& filename) const;
};


#endif // LEVEL_H