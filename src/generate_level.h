#ifndef GENERATE_LEVEL.H
#define GENERATE_LEVEL.H

#include <string>

#include <Graph_lib/GUI.h>
#include "main_window.h"

struct Generate_level_window: public Window_with_back
{
public:
    Generate_level_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper& own);

    static void cb_save_button(Graph_lib::Address, Graph_lib::Address addr);
    void save_button();

private:
    Graph_lib::Choice_box size_box;
    Graph_lib::File_chooser_box image_chooser;
    Windows_wrapper& own;
    static void cb_choose_file(Graph_lib::Address, Graph_lib::Address);
    static void save_image(const std::string&);
};

#endif // GENERATE_LEVEL.H