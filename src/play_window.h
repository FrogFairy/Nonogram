#ifndef PLAY_WINDOW_H
#define PLAY_WINDOW_H

#include "main_window.h"
#include "database.h"
#include "graph_board.h"

class Fill_button : public Graph_lib::Button
{
public:
    enum Button_type {FILLED, CROSS};

    Fill_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active, Button_type b_type);

    ~Fill_button() { delete mark; }

    void attach(Graph_lib::Window& win)
    {
        Graph_lib::Button::attach(win);
        win.attach(*mark);
        set_color();
    }

    virtual void change_color()
    {
        active = !active;
        set_color();
    }

    void set_color();
    
    bool active;

private:
    Graph_lib::Shape* mark;
};


struct Play_window : public Window_with_back
{
public:
    Play_window(Graph_lib::Point xy, int w, int h, const std::string& title, Level& level, Windows_wrapper &own);

    Game_button::State option() { return button_option; }

    void update_current(Level& level);
    void update_finished(Level& level);
    void update_heart_count(Level& level);

private:
    static void cb_rules(Graph_lib::Address, Graph_lib::Address addr);
    void rules();

    static void cb_hint(Graph_lib::Address, Graph_lib::Address addr);
    void hint();

    static void cb_restart(Graph_lib::Address, Graph_lib::Address addr);
    void restart();

    static void cb_choose_option(Graph_lib::Address, Graph_lib::Address addr);
    void choose_option();

    Graph_board board;

    Windows_wrapper& own;

    Graph_lib::Button rules_button;
    Graph_lib::Button hint_button;
    Graph_lib::Button restart_button;
    Graph_lib::Image lamp;

    Fill_button filled_button;
    Fill_button cross_button;
    Game_button::State button_option;

    Graph_lib::Vector_ref<Graph_lib::Image> hearts_img;
};


#endif  // PLAY_WINDOW_H