#ifndef PLAY_WINDOW_H
#define PLAY_WINDOW_H

#include "main_window.h"
#include "database.h"
#include "graph_board.h"

struct Fill_button : public Graph_lib::Button
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

struct Heart : public Graph_lib::Widget
{
public:
    Heart(Graph_lib::Point xy, int w, int h, bool fill)
    : Graph_lib::Widget{xy, w, h, "", nullptr}, filled{fill}
    {
        img = new Graph_lib::Image(loc, (filled ? fill_heart : empty_heart));
    }

    // ~Heart() { delete img; }

    void attach(Graph_lib::Window& win) 
    {
        pw = new Fl_Box(FL_NO_BOX, loc.x, loc.y, width, height, "");
        pw->image(img->fl_image());
        own = &win;
    }

    void change(bool fill)
    {
        if (fill == filled) return;
        filled = fill;
        pw->deimage();
        delete img;
        img = new Graph_lib::Image(loc, (filled ? fill_heart : empty_heart));
        pw->image(img->fl_image());
        pw->redraw();
    }

    bool is_filled() { return filled; }

private:
    bool filled;
    Graph_lib::Image* img;

    const std::string fill_heart = "resources/heart.png";
    const std::string empty_heart = "resources/empty_heart.png";
};


struct Play_window : public Window_with_back
{
public:
    Play_window(Graph_lib::Point xy, int w, int h, const std::string& title, Level& level, Windows_wrapper &own);
    // ~Play_window() { delete board; }

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
    Level level;

    Windows_wrapper& own;

    Graph_lib::Button rules_button;
    Graph_lib::Button hint_button;
    Graph_lib::Button restart_button;
    Graph_lib::Image lamp;

    Fill_button filled_button;
    Fill_button cross_button;
    Game_button::State button_option;

    std::vector<Heart> hearts_img;
};


#endif  // PLAY_WINDOW_H