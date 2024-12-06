#ifndef CHOOSE_LEVEL_H
#define CHOOSE_LEVEL_H

#include <string>

#include <Graph_lib/GUI.h>
#include "main_window.h"
#include "database.h"

struct Level_button: public Graph_lib::Button
{
public:
    Level_button(Graph_lib::Point xy, int w, int h, const std::string& name_of_level, Graph_lib::Callback cb, bool is_finished)
        : Graph_lib::Button{xy, w, h, name_of_level, cb}
    {
        color = (is_finished ? FL_DARK_GREEN : FL_BACKGROUND_COLOR);
    }

    void attach(Graph_lib::Window& win)
    {
        Graph_lib::Button::attach(win);
        pw->color(color);
    }

private:
    Fl_Color color;
};

struct Choose_level_window : public Window_with_back
{
public:
    Choose_level_window(Graph_lib::Point xy, int w, int h, const std::string &title, const std::string &size, Windows_wrapper& own);

private:
    static void cb_start_level(Graph_lib::Address, Graph_lib::Address addr);
    void start_level(const std::string& title);

    std::string btn_label;
    Graph_lib::Menu level_widget;
    std::vector<Level> levels;
    Graph_lib::Vector_ref<Level_button*> level_buttons;
    Windows_wrapper& own;
};

#endif // CHOOSE_LEVEL_H