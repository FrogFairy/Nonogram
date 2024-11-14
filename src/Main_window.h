
#include <Graph_lib/GUI.h>
#include <Graph_lib/Window.h>
#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

class Main_window : Graph_lib::Window
{
    public:

    Main_window(Graph_lib::Point xy, int w, int h, const std::string &title);

    private:
    Graph_lib::Menu levels_menu;
    Graph_lib::Button generate_button;
    
    static void cb_go_to_level(Graph_lib::Address, Graph_lib::Address widget);
    static void cb_create_level(Graph_lib::Address, Graph_lib::Address widget);

    static void go_to_level(Graph_lib::Widget& Button);
    static void create_level(Graph_lib::Widget& Button);
};