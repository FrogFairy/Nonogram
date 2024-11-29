#include "choose_level.h"
#include "main_window.h"

void Choose_level_window::cb_start_level(Graph_lib::Address, Graph_lib::Address addr) 
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Choose_level_window&>(pb->window()).start_level();
}

void Choose_level_window::start_level()
{
    Window_with_back win {p, w, h, title};
    this->hide();
    win.wait_for_button();
    this->show();
}

Choose_level_window::Choose_level_window(Graph_lib::Point xy, int w, int h, const std::string &title, const std::string &btn_label)
    : Window_with_back{xy, w, h, title}, p{xy}, w{w}, h{h}, title{title},
    level_widget{Graph_lib::Point{260, 250}, 200, 50, Graph_lib::Menu::vertical, "widget_for_choose_level_window"}
{
    Graph_lib::Menu level_widget {Graph_lib::Point{260, 250}, 200, 50, Graph_lib::Menu::vertical, "levels"};

    Graph_lib::Button level_1 {Graph_lib::Point{0, 0}, 0, 0, "1 level", cb_start_level};
    Graph_lib::Button level_2 {Graph_lib::Point{0, 0}, 0, 0, "2 level", cb_start_level};
    Graph_lib::Button level_3 {Graph_lib::Point{0, 0}, 0, 0, "3 level", cb_start_level};
    Graph_lib::Button level_4 {Graph_lib::Point{0, 0}, 0, 0, "4 level", cb_start_level};

    level_widget.attach(level_1);
    level_widget.attach(level_2);
    level_widget.attach(level_3);
    level_widget.attach(level_4);

    attach(level_widget); 
}