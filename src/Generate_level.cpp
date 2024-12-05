#include "generate_level.h"
#include "wrapper.h"

#include <iostream>
#include <typeinfo>

void Generate_level_window::cb_save_button(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Generate_level_window&>(pb->window()).save_button();
}
void Generate_level_window::save_button()
{
    // std::cout << size_box.current_value() << std::endl;
    switch(size_box.get_value())
    {
        case 0:
            level_size = "10x10";
            break;
        case 1:
            level_size = "15x15";
            break;
        case 2:
            level_size = "20x20";
            break;

    }
    str_level_name = level_name.get_string();
    
    if (str_level_name=="")
    {
        str_level_name = "level " + std::to_string(own.db_levels.get_new_id(level_size));
    }

    if(filename=="")
    {
        empty_path.put("please specify the path to the file");
    }
    else
    {
        Database_levels::Response res = own.db_levels.add_level(Level {str_level_name, 
                                                                   level_size, filename});
        button_pushed = true;
    }
}

//добавить inbox название 
Generate_level_window::Generate_level_window(Graph_lib::Point xy, int w, int h, 
                                            const std::string &title, Windows_wrapper& own)
: Window_with_back{xy, w, h, title}, own{own},
size_box{Graph_lib::Point{260, 250}, 200, 50, "size"},
image_chooser{Graph_lib::Point{260, 350}, 200, 50, " ", "choose image", "Image Files (*.{jpg,png})", save_image, cb_choose_file},
empty_path {Graph_lib::Point{230, 200}, 250, 20, ""},
level_name{Graph_lib::Point{260, 400}, 200, 30, "level name:"}
{
    attach(image_chooser);
    attach(size_box);
    size_box.add("10x10");
    size_box.add("15x15");
    size_box.add("20x20");
    size_box.set_value(0);

    Graph_lib::Button save_button {Graph_lib::Point{590, 670}, 100, 20, "save", cb_save_button};
    attach(save_button);
    attach(empty_path);
    attach(level_name);
    empty_path.put("input data for create level");
}

void Generate_level_window::cb_choose_file(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Generate_level_window&>(pb->window()).image_chooser.choose_file();
}

void Generate_level_window::save_image(Graph_lib::Window *own, const std::string& filename) {
    static_cast<Generate_level_window*>(own)->filename = filename;
};