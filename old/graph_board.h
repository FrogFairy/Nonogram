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

    void change_button(State state);
    void init_mark();

    int x() { return x_coord; }
    int y() { return y_coord; }

    void block(bool state) { blocked = state; }

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
        if (level.hearts_count == 0 || level.finished) block_buttons(false);
    }

    // ~Graph_board() 
    // {
    //     for (int i = 0; i < row_digits.size(); ++i)
    //     {
    //         for (int j = 0; j < row_digits[i].size(); ++j)
    //             delete &row_digits[i][j];
    //     }

    //     for (int i = 0; i < col_digits.size(); ++i)
    //     {
    //         for (int j = 0; j < col_digits[i].size(); ++j)
    //             delete &col_digits[i][j];
    //     }
    // }

    void restart()
    {
        level.restart();
        logic_board = Logic_board(level);
        mistake = std::vector<int> {};
        hint = std::vector<int> {};
        block_buttons(false);
        change_buttons(false);
    }

    void change_buttons(bool state);
    void change_digits();
    void init();
    void get_hint();

    bool is_blocked() { return blocked; }

    void attach(Graph_lib::Window &win);

    void block_buttons(bool state);

    void redraw() override;
    
private:
    static void cb_click_button(Graph_lib::Address, Graph_lib::Address addr);
    void click_button(Game_button* btn);

    void change_previous();
    void change_digit(int x, int y);
    void set_digit_color(Graph_lib::Label_widget* text, Graph_lib::Color color);

    Graph_lib::Vector_ref<Game_button> buttons {};
    std::vector<Graph_lib::Vector_ref<Graph_lib::Label_widget>> row_digits {};
    std::vector<Graph_lib::Vector_ref<Graph_lib::Label_widget>> col_digits {};

    Logic_board logic_board;
    Level level;

    std::vector<int> mistake {}; // coord mistake cell
    std::vector<int> hint {}; // coord hint cell

    bool blocked = false;
};


#endif // GRAPH_BOARD_H