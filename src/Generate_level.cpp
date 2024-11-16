#include "Generate_level.h"
#include "Main_window.h"

Generate_level_window::Generate_level_window(Graph_lib::Point xy, int w, int h, const std::string &title)
: Window_with_back{xy, w, h, title}, p{xy}, w{w}, h{h}, title{title},
size{Graph_lib::Point{260, 250}, 200, 50, Graph_lib::Menu::vertical, "size"}
{
    size -> add("10 x 10");
    size -> add("15 x 15");
    size.attach();
}