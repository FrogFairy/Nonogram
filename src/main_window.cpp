#include "main_window.h"
#include "wrapper.h"
#include "database.h"

void Main_window::cb_go_to_level(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Size_button*>(addr);
    static_cast<Main_window&>(pb->window()).go_to_level(pb->level_size());
}

void Main_window::cb_create_level(Graph_lib::Address, Graph_lib::Address addr) 
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Main_window&>(pb->window()).create_level();
}

void Main_window::go_to_level(Size btn_label)
{
    own.open_choose_window(btn_label);
}

void Main_window::create_level()
{
    own.open_generate_window();
}

Main_window::Main_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper& own)
    : Graph_lib::Window{xy, w, h, title}, own{own},
    main_widget{Graph_lib::Point{260, 250}, 200, 50, Graph_lib::Menu::vertical, "widget_for_main_window"}
{
    Graph_lib::Window::size_range(w, h, w, h);
    Graph_lib::Menu levels_menu {Graph_lib::Point{260, 250}, 200, 50, Graph_lib::Menu::vertical, "levels"};

    for (unsigned int i = 0; i < 30; i += 5)
    {
        Size_button button {Graph_lib::Point{0, 0}, 0, 0, Size(i, i), cb_go_to_level};
        size_buttons.push_back(button);
        main_widget.attach(button);
    }

    Graph_lib::Button generate_button {Graph_lib::Point{260, 180}, 200, 50, "Generate level", cb_create_level};
    main_widget.attach(generate_button);
    attach(main_widget); 
}

