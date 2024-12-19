#ifndef CHOOSE_LEVEL_H
#define CHOOSE_LEVEL_H

#include <string>
#include <algorithm>

#include "constants.h"
#include <Graph_lib/GUI.h>
#include "main_window.h"
#include "../Logic_classes/database.h"

struct Level_button: public Graph_lib::Button
{
public:
    Level_button(Graph_lib::Point xy, int w, int h, const std::string& name_of_level, Graph_lib::Callback cb, bool is_finished)
        : Graph_lib::Button{xy, w, h, name_of_level, cb}
    {
        color = (is_finished ? dark_green : default_color);
    }

    void attach(Graph_lib::Window& win)
    {
        Graph_lib::Button::attach(win);
        pw->color(color);
        pw->color2(color);
    }

    void change_color(bool is_finished)
    {
        color = (is_finished ? dark_green : default_color);
        pw->color(color);
        pw->color2(color);
    }

private:
    Fl_Color color;
};

struct Choose_level_window : public Window_with_back
{
public:
    Choose_level_window(Graph_lib::Point xy, int w, int h, const std::string &title, Size size, Windows_wrapper& own);

private:
    static void cb_start_level(Graph_lib::Address, Graph_lib::Address addr);
    void start_level(const std::string& title, Level_button& btn);

    Size size;
    Graph_lib::Menu level_widget;
    // Graph_lib::Scrollable_Menu scroll_widget;
    std::vector<Level> levels;
    Graph_lib::Vector_ref<Level_button*> level_buttons;
    Windows_wrapper& own;
};

#endif // CHOOSE_LEVEL_H