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
    Fill_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active)
                : Graph_lib::Button{xy, w, h, label, cb}, active{active} {}

    void attach(Graph_lib::Window& win)
    {
        Graph_lib::Button::attach(win);
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
            pw->color(Graph_lib::Color::black);
            pw->color2(Graph_lib::Color::black);
        }
    }
    
    bool active;

private:
};


#endif // BUTTONS_H