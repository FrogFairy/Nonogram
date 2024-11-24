#include "Main_window.h"
#include "Generate_level.h"
#include "Choose_level.h"

void Main_window::cb_go_to_level(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Main_window&>(pb->window()).go_to_level(pb->label);
}

void Main_window::cb_create_level(Graph_lib::Address, Graph_lib::Address addr) 
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Main_window&>(pb->window()).create_level();
}

void Main_window::go_to_level(std::string btn_label)
{
    Choose_level_window win {p, w, h, title, btn_label}; // создавать окно с уровнями; передавать в него label кнопки, на котором указаны размеры поля
    this->hide();
    win.wait_for_button();
    this->show();
}

void Main_window::create_level()
{
    Generate_level_window win {p, w, h, title};
    this->hide();
    win.wait_for_button();
    this->show();
}

Main_window::Main_window(Graph_lib::Point xy, int w, int h, const std::string &title)
    : Graph_lib::Window{xy, w, h, title}, p{xy}, w{w}, h{h}, title{title},
    main_widget{Graph_lib::Point{260, 250}, 200, 50, Graph_lib::Menu::vertical, "widget_for_main_window"}
{
    Graph_lib::Menu levels_menu {Graph_lib::Point{260, 250}, 200, 50, Graph_lib::Menu::vertical, "levels"};
    Graph_lib::Button button_1 {Graph_lib::Point{0, 0}, 0, 0, "10x10", cb_go_to_level};
    Graph_lib::Button button_2 {Graph_lib::Point{0, 0}, 0, 0, "15x15", cb_go_to_level};
    Graph_lib::Button button_3 {Graph_lib::Point{0, 0}, 0, 0, "20x20", cb_go_to_level};
    Graph_lib::Button generate_button {Graph_lib::Point{260, 180}, 200, 50, "Generate level", cb_create_level};
    main_widget.attach(generate_button);
    main_widget.attach(button_1);
    main_widget.attach(button_2);
    main_widget.attach(button_3);
    attach(main_widget); 
}

