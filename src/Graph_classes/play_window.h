#ifndef PLAY_WINDOW_H
#define PLAY_WINDOW_H

#include <Graph_lib/GUI.h>
#include "main_window.h"
#include "../Logic_classes/database.h"
#include "graph_board.h"

#include <memory>

struct Option_button : public Graph_lib::Button
{
public:
    Option_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active)
        : Graph_lib::Button{xy, w, h, label, cb}, _active{active}, 
        default_color{Graph_lib::Color::black}, active_color{Graph_lib::Color::dark_green}
        {};

    virtual void attach(Graph_lib::Window& win)
    {
        Graph_lib::Button::attach(win);
        win.attach(*mark);
        set_color();
    }

    virtual void change_state()
    {
        _active = !_active;
        set_color();
    }

    void set_color();
    bool active() { return _active; }

protected:
    std::unique_ptr<Graph_lib::Shape> mark;
    const int margin = 5;
    Graph_lib::Color default_color;
    Graph_lib::Color active_color;

private:
    bool _active;
};

struct Fill_button : public Option_button
{
    Fill_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active);
};

struct Cross_button : public Option_button
{
    Cross_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active);
};

struct Invert_button : public Option_button
{
public:
    Invert_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active);
    void attach(Graph_lib::Window& win) override;

private:
    std::unique_ptr<Graph_lib::Label_widget> label_widget;
};

struct Heart : public Graph_lib::Widget
{
public:
    Heart(Graph_lib::Point xy, int w, int h, bool fill)
    : Graph_lib::Widget{xy, w, h, "", nullptr}, filled{fill}
    {}

    Heart(const Heart& other)
    : Graph_lib::Widget{other}, img{other.img}, filled{other.filled}
    {}

    void attach(Graph_lib::Window& win) 
    {
        img = new Graph_lib::Image(loc, (filled ? fill_heart : empty_heart));
        pw = new Fl_Box(FL_NO_BOX, loc.x, loc.y, width, height, "");
        pw->image(img->fl_image());
        own = &win;
    }

    void clean_pointer()
    {
        pw->deimage();
        Graph_lib::Widget::clean_pointer();
        delete img;
    }

    void change(bool fill)
    {
        if (fill == filled) return;
        filled = fill;
        // pw->deimage();
        // delete img;
        // img = new Graph_lib::Image(loc, (filled ? fill_heart : empty_heart));
        // pw->image(img->fl_image());
        // pw->redraw();
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

    ~Play_window()
    {
        for (Heart heart : hearts_img)
            heart.clean_pointer();
    }

    Level::Cell_state option() { return button_option; }

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

    static void cb_invert(Graph_lib::Address, Graph_lib::Address addr);
    void invert();

    Graph_board board;
    Level level;

    Windows_wrapper& own;

    Graph_lib::Button rules_button;
    Graph_lib::Button hint_button;
    Graph_lib::Button restart_button;
    Graph_lib::Image lamp;

    Fill_button filled_button;
    Cross_button cross_button;
    Invert_button invert_button;
    Level::Cell_state button_option;

    std::vector<Heart> hearts_img;

    const std::string text_finish = "you have completed this level!";
    const std::string text_hearts = "you've run out of hearts.";
};


#endif  // PLAY_WINDOW_H