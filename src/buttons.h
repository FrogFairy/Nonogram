#ifndef BUTTONS_H
#define BUTTONS_H

#include <Graph_lib/GUI.h>
#include <Graph_lib/Graph.h>

struct Game_button : public Graph_lib::Button
{
public:
    // enum class State
    // {
    //     EMPTY = -1;
    //     CROSS = 0;
    //     FILLED = 1;
    // };

    Game_button(Graph_lib::Point xy, int w, int h, const std::string &label, Graph_lib::Callback cb, int value) : Graph_lib::Button{xy, w, h, label, cb} {}
    void attach(Window& win);

    void change_button();

private:
    
};

class Fill_button : public Graph_lib::Button
{
public:
    enum Button_type {FILLED, CROSS};

    Fill_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active, Button_type b_type)
                : Graph_lib::Button{xy, w, h, label, cb}, active{active} 
    {
        int margin = 5;
        if (b_type == Button_type::FILLED)
        {
            mark = new Graph_lib::Rectangle(Graph_lib::Point(xy.x + margin, xy.y + margin), w - margin * 2, h - margin * 2);
        }
        else
        {
            mark = new Graph_lib::Lines;
            ((Graph_lib::Lines*)mark)->add(Graph_lib::Point(xy.x + margin, xy.y + margin), Graph_lib::Point(xy.x + w - margin, xy.y + h - margin));
            ((Graph_lib::Lines*)mark)->add(Graph_lib::Point(xy.x + margin, xy.y + h - margin), Graph_lib::Point(xy.x + w - margin, xy.y + margin));
            mark->set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 3));
        }
        mark->set_color(Graph_lib::Color::black);
        mark->set_fill_color(Graph_lib::Color::black);
    }

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

    void set_color()
    {
        if (active)
        {
            pw->color(Graph_lib::Color::dark_green);
            pw->color2(Graph_lib::Color::dark_green);
        }
        else
        {
            pw->color(Graph_lib::Color::no_color);
            pw->color2(Graph_lib::Color::no_color);
        }
    }
    
    bool active;

private:
    Graph_lib::Shape* mark;
};


#endif // BUTTONS_H