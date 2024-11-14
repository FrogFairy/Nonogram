#include "Main_window.h"

void Main_window::cb_go_to_level(Graph_lib::Address, Graph_lib::Address widget)
{
    auto &btn = Graph_lib::reference_to<Graph_lib::Widget>(widget);
    go_to_level(btn);
}

void Main_window::cb_create_level(Graph_lib::Address, Graph_lib::Address widget)
{
    auto &btn = Graph_lib::reference_to<Graph_lib::Widget>(widget);
    create_level(btn);
}

void Main_window::go_to_level(Graph_lib::Widget &Button)
{
    Graph_lib::Simple_window win = Graph_lib::Simple_window{Graph_lib::Point{400, 100}, 100, 100, "New Window"};
    win.wait_for_button();
} // в аргументы к новому окну передавать размеры поля

void Main_window::create_level(Graph_lib::Widget &Button)
{
    Graph_lib::Window win = Graph_lib::Window{Graph_lib::Point{400, 100}, 100, 100, "New Window"};
    // hide();
} // в аргументы к новому окну передавать размеры поля

Main_window::Main_window(Graph_lib::Point xy, int w, int h, const std::string &title)
    : Graph_lib::Window{xy, w, h, title},
      levels_menu{Graph_lib::Point{260, 250}, 200, 50, Graph_lib::Menu::vertical, "levels"},
      generate_button{Graph_lib::Point{260, 180}, 200, 50, "Сгенерировать уровень", cb_create_level}
{
    levels_menu.attach(new Graph_lib::Button{Graph_lib::Point{0, 0}, 0, 0, "10x10", cb_go_to_level});
    levels_menu.attach(new Graph_lib::Button{Graph_lib::Point{0, 0}, 0, 0, "15x15", cb_go_to_level});
    levels_menu.attach(new Graph_lib::Button{Graph_lib::Point{0, 0}, 0, 0, "20x20", cb_go_to_level});
    attach(levels_menu);
    attach(generate_button);
};