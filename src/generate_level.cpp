#include "generate_level.h"
#include "wrapper.h"

void Generate_level_window::cb_save_button(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Generate_level_window&>(pb->window()).save_button();
}
void Generate_level_window::save_button()
{
    // здесь реализация сохранения в базу данных
    button_pushed = true;
}

Generate_level_window::Generate_level_window(Graph_lib::Point xy, int w, int h, 
                                            const std::string &title, Windows_wrapper& own)
: Window_with_back{xy, w, h, title}, own{own},
size_box{Graph_lib::Point{260, 250}, 200, 50, "size"},
image_chooser{Graph_lib::Point{260, 350}, 200, 50, " ", "choose image", "Image Files (*.{jpg,png})", save_image, cb_choose_file}
{
    attach(image_chooser);
    attach(size_box);
    size_box.add("10 x 10");
    size_box.add("15 x 15");
    size_box.add("20 x 20");

    Graph_lib::Button save_button {Graph_lib::Point{590, 670}, 100, 20, "save", cb_save_button};
    attach(save_button);
}

void Generate_level_window::cb_choose_file(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Generate_level_window&>(pb->window()).image_chooser.choose_file();
}

void Generate_level_window::save_image(const std::string&) {};
