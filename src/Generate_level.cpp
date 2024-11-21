#include "Generate_level.h"
#include "Main_window.h"

void Generate_level_window::cb_save_button(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Generate_level_window&>(pb->window()).save_button();
}

void Generate_level_window::save_button()
{
    Generate_level_window win {p, w, h, title};
    this->hide();
    win.wait_for_button();
    this->show();
}

Generate_level_window::Generate_level_window(Graph_lib::Point xy, int w, int h, const std::string &title)
: Window_with_back{xy, w, h, title}, p{xy}, w{w}, h{h}, title{title},
size_box{Graph_lib::Point{260, 250}, 200, 50, "size"}
{
    attach(size_box);
    size_box.add("10 x 10");
    size_box.add("15 x 15");
    size_box.add("20 x 20");

    Graph_lib::Button save_button {Graph_lib::Point{590, 670}, 100, 20, "save", cb_save_button};
    attach(save_button);
}