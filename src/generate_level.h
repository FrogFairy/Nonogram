#ifndef GENERATE_LEVEL_H
#define GENERATE_LEVEL_H

#include <string>

#include <Graph_lib/GUI.h>
#include "main_window.h"
#include "database.h"

struct Generate_level_window: public Window_with_back
{
public:
    Generate_level_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper& own);

private:
    std::string filename;
    Size level_size;
    std::string str_level_name;

    std::vector<Size> sizes;

    Graph_lib::Choice_box size_box;
    Graph_lib::File_chooser_box image_chooser;
    Graph_lib::In_box level_name;

    Windows_wrapper& own;

    static void cb_choose_file(Graph_lib::Address, Graph_lib::Address);
    static void save_image(Graph_lib::Window *own, const std::string&);
    static void cb_save_button(Graph_lib::Address, Graph_lib::Address addr);

    void save_button();
};

#endif // GENERATE_LEVEL_H
