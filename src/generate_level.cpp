#include "generate_level.h"
#include "wrapper.h"

#include <iostream>
#include <typeinfo>

void Generate_level_window::cb_save_button(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Generate_level_window&>(pb->window()).save_button();
}

void Generate_level_window::init_hidden_digits(Level& level)
{
    Logic_board logic_board {level};
    for (int i = 0; i < logic_board.row_intervals.size(); ++i)
    {
        for (int j = 0; j < logic_board.row_intervals[i].size(); ++j)
        {
            if (logic_board.row_intervals[i][j].empty())
                level.empty_rows.push_back(std::vector<int> {i, j});
        }
    }

    for (int i = 0; i < logic_board.col_intervals.size(); ++i)
    {
        for (int j = 0; j < logic_board.col_intervals[i].size(); ++j)
        {
            if (logic_board.col_intervals[i][j].empty())
                level.empty_cols.push_back(std::vector<int> {i, j});
        }
    }
}

void Generate_level_window::save_button()
{
    level_size = sizes[size_box.get_value()];

    str_level_name = level_name.get_string();
    
    if (str_level_name == "")
    {
        str_level_name = "level " + std::to_string(own.db_levels.get_new_id(level_size));
    }

    if(filename == "")
    {
        exception_label.set_label("please specify the path to the image");
    }
    else
    {
        Level level {str_level_name, level_size, filename};
        level.init();
        init_hidden_digits(level);

        Database_levels::Response res = own.db_levels.add_level(level);
        if (res == Database_levels::ALREADY_EXISTS) 
        {
            exception_label.set_label("level with this size and title already exists");
            return;
        }
        button_pushed = true;
    }
}

Generate_level_window::Generate_level_window(Graph_lib::Point xy, int w, int h, 
                                            const std::string &title, Windows_wrapper& own)
: Window_with_back{xy, w, h, title}, own{own},
size_box{Graph_lib::Point{260, 250}, 200, 50, "size: "},
image_chooser{Graph_lib::Point{260, 350}, 200, 50, " ", "choose image", "Image Files (*.{jpg,png})", save_image, cb_choose_file},
exception_label {Graph_lib::Point{210, 450}, ""},
level_name{Graph_lib::Point{260, 400}, 200, 30, "level name: "}
{
    Window_with_back::size_range(w, h, w, h);

    attach(size_box);
    for (unsigned int i = 10; i < 30; i += 5)
    {
        Size s = Size(i, i);
        sizes.push_back(s);
        size_box.add(to_string(s));
    }
    size_box.set_value(0);

    attach(image_chooser);

    Graph_lib::Button save_button {Graph_lib::Point{590, 670}, 100, 20, "save", cb_save_button};
    attach(save_button);
    attach(level_name);

    attach(exception_label);
}

void Generate_level_window::cb_choose_file(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Generate_level_window&>(pb->window()).image_chooser.choose_file();
}

void Generate_level_window::save_image(Graph_lib::Window *own, const std::string& filename) {
    static_cast<Generate_level_window*>(own)->filename = filename;
};