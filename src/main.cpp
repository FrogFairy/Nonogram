#include <iostream>
#include <Graph_lib/GUI.h>
#include <Graph_lib/Window.h>
#include <Graph_lib/Graph.h>


class Main_window : Graph_lib::Window
{
    public:

    Main_window(Graph_lib::Point xy, int w, int h, const std::string &title);

    private:
    Graph_lib::Menu levels_menu;
    
    static void cb_level(Graph_lib::Address, Graph_lib::Address widget)
    {
        auto &btn = Graph_lib::reference_to<Graph_lib::Widget>(widget);
        go_to_level(btn);
    }
    static void go_to_level(Graph_lib::Widget& Button){
        Graph_lib::Window win=Graph_lib::Window{Graph_lib::Point{100,100},100,100, "New Window"};
        win.show();
    } //в аргументы к новому окну передавать размеры поля


};

Main_window::Main_window(Graph_lib::Point xy, int w, int h, const std::string &title)
    : Graph_lib::Window{xy, w, h, title},
    levels_menu{Graph_lib::Point{0, 0}, 100, 100, Graph_lib::Menu::vertical, "levels"}
    {
        levels_menu.attach(new Graph_lib::Button{Graph_lib::Point{0, 0}, 10, 10, "10x10", cb_level});
        attach(levels_menu);
    };

int main()
{
    Main_window win{Graph_lib::Point{100, 100}, 300, 400, "window"};
    return Graph_lib::gui_main();
}