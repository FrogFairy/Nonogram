#include "Generate_level.h"
#include "Main_window.h"

Generate_level_window::Generate_level_window(Graph_lib::Point xy, int w, int h, const std::string &title)
: Window_with_back{xy, w, h, title}, p{xy}, w{w}, h{h}, title{title},
size_box{Graph_lib::Point{260, 250}, 200, 50, "size"},
image_chooser{Graph_lib::Point{260, 350}, 200, 50, " ", "choose image", "Image Files (*.{jpg,png})", save_image, cb_choose_file}
{
    attach(image_chooser);
    attach(size_box);
    size_box.add("10 x 10");
    size_box.add("15 x 15");
    size_box.add("20 x 20");
}

void Generate_level_window::cb_choose_file(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Generate_level_window&>(pb->window()).image_chooser.choose_file();
}

void Generate_level_window::save_image(const std::string&) {};