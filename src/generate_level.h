#ifndef GENERATE_LEVEL_H
#define GENERATE_LEVEL_H

#include <string>

#include <Graph_lib/GUI.h>
#include "main_window.h"
#include "database.h"

struct Empty_image_chooser : Graph_lib::Widget
{
public:
    Empty_image_chooser(Graph_lib::Point xy, const std::string& title)
        : Graph_lib::Widget{xy, 300, 50, "exception empty path", nullptr}, label{xy, title} {}
    void attach (Graph_lib::Window& win)
    {
        win.attach(label);
        own = &win;
    }

private:
    Graph_lib::Text label;
};

struct Generate_level_window: public Window_with_back
{
public:
    Generate_level_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper& own);

    static void cb_save_button(Graph_lib::Address, Graph_lib::Address addr);
    void save_button();

private:
    std::string filename;
    std::string level_size;
    Graph_lib::Choice_box size_box;
    Graph_lib::File_chooser_box image_chooser;
    Empty_image_chooser empty_path;
    Windows_wrapper& own;

    static void cb_choose_file(Graph_lib::Address, Graph_lib::Address);
    static void save_image(Graph_lib::Window *own, const std::string&);
};

#endif // GENERATE_LEVEL_H
