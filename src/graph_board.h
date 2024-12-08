#ifndef GRAPH_BOARD_H
#define GRAPH_BOARD_H

#include <Graph_lib/GUI.h>
#include <Graph_lib/Graph.h>
#include "database.h"
#include "logic_board.h"

#include <vector>
#include <algorithm>

struct Graph_board;

struct Game_button : public Graph_lib::Button
{
public:
    enum State
    {
        EMPTY = -1,
        CROSS = 0,
        FILLED = 1,
        HINT_CROSS = 2,
        HINT_FILLED = 3,
        MISTAKE_CROSS = 4,
        MISTAKE_FILLED = 5
    };

    Game_button(Graph_lib::Point xy, int w, int h, const std::string &label, Graph_lib::Callback cb, int x, int y, State state, Graph_board& board)
        : Graph_lib::Button{xy, w, h, label, cb}, x_coord{x}, y_coord{y}, cur_state{state}, board{board}, mark{nullptr}, blocked{false}
    {
        if (state != State::EMPTY) 
        {
            init_mark();
        }
    }

    ~Game_button() { delete mark; }

    void attach(Graph_lib::Window& win)
    {
        Graph_lib::Button::attach(win);
        pw->color(Graph_lib::Color::white);
        pw->color2(Graph_lib::Color::white);
        if (mark)
            win.attach(*mark);
    }

    void change_button(State state);
    void init_mark();

    int x() { return x_coord; }
    int y() { return y_coord; }

    void block() { blocked = !blocked; }

    Game_button::State state() { return cur_state; }

    Graph_board& board;

private:
    int x_coord, y_coord;
    bool blocked;

    State cur_state;
    Graph_lib::Shape* mark;
};

struct Graph_board : public Graph_lib::Widget
{
public:
    Graph_board(Graph_lib::Point xy, int w, int h, Level& level)
        : Widget{xy, w, h, "", nullptr}, level{level}, logic_board{Logic_board(level)}
    {
        init();
        if (level.hearts_count == 0 || level.finished) block_buttons();
    }

    void init();
    void attach(Graph_lib::Window &win);

    void block_buttons();
    
private:
    static void cb_click_button(Graph_lib::Address, Graph_lib::Address addr);
    void click_button(Game_button* btn);

    void change_previous();

    Graph_lib::Vector_ref<Game_button> buttons;
    std::vector<Graph_lib::Vector_ref<Graph_lib::Text>> row_digits;
    std::vector<Graph_lib::Vector_ref<Graph_lib::Text>> col_digits;

    Logic_board logic_board;
    Level level;

    std::vector<int> mistake; // coord mistake cell
    std::vector<int> hint; // coord hint cell

    bool is_blocked = false;
};


#endif // GRAPH_BOARD_H