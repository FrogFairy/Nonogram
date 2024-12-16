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
    Game_button(Graph_lib::Point xy, int w, int h, const std::string &label, Graph_lib::Callback cb, int x, int y, Level::Cell_state state, Graph_board& board)
        : Graph_lib::Button{xy, w, h, label, cb}, x_coord{x}, y_coord{y}, cur_state{state}, board{board}, blocked{false}
    {
        init_mark();
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

    void change_button(Level::Cell_state state);
    void init_mark();

    int x() { return x_coord; }
    int y() { return y_coord; }

    void block(bool state) { blocked = state; }

    Level::Cell_state state() { return cur_state; }

    Graph_board& board;

private:
    int x_coord, y_coord;
    bool blocked;

    Level::Cell_state cur_state;
    Graph_lib::Shape* mark;
};

struct Graph_board : public Graph_lib::Widget
{
public:
    Graph_board(Graph_lib::Point xy, int w, int h, Level& level)
        : Widget{xy, w, h, "", nullptr}, level{level}, logic_board{Logic_board(level)}
    {
        init_buttons();
        init_digits();
        if (level.hearts_count == 0 || level.finished) block_buttons(true);
    }

    void restart()
    {
        level.restart();
        logic_board = Logic_board(level);
        mistake = Position {};
        hint = Position {};
        block_buttons(false);
        change_buttons(false);
    }
    
    void init_buttons();
    void init_digits();

    void get_hint();

    Level invert_digits();

    bool is_blocked() { return blocked; }

    void attach(Graph_lib::Window &win);
    void detach();

    void redraw() override;
    
private:
    static void cb_click_button(Graph_lib::Address, Graph_lib::Address addr);
    void click_button(Game_button* btn);

    void change_previous();
    void change_buttons(bool state);
    void change_digits(Position pos);

    void set_digit_color(Graph_lib::Text& text, Graph_lib::Color color);
    void block_buttons(bool state);

    void detach_digits();
    void attach_digits(Graph_lib::Window& win);

    Graph_lib::Vector_ref<Game_button> buttons;
    std::vector<Graph_lib::Vector_ref<Graph_lib::Text>> row_digits;
    std::vector<Graph_lib::Vector_ref<Graph_lib::Text>> col_digits;

    Logic_board logic_board;
    Level level;

    Position mistake {}; // coord mistake cell
    Position hint {}; // coord hint cell

    bool blocked = false;
};


#endif // GRAPH_BOARD_H