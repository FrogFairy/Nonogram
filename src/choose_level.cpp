#include "choose_level.h"
#include "wrapper.h"

void Choose_level_window::cb_start_level(Graph_lib::Address, Graph_lib::Address addr) 
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Choose_level_window&>(pb->window()).start_level(pb->label);
}

void Choose_level_window::start_level(const std::string& title)
{
    own.open_play_window(btn_label, title);
}

Choose_level_window::Choose_level_window(Graph_lib::Point xy, int w, int h, const std::string &title, const std::string &size, Windows_wrapper& own)
    : Window_with_back{xy, w, h, title}, 
    level_widget{Graph_lib::Point{260, 250}, 200, 50, Graph_lib::Menu::vertical, "widget_for_main_window"}, own{own}
{
    Graph_lib::Menu level_widget {Graph_lib::Point{260, 250}, 200, 50, Graph_lib::Menu::vertical, "levels"};

    levels = own.db_levels.get_levels(size);
    for (Level level : levels)
    {
        Level_button* level_button {new Level_button{Graph_lib::Point{0, 0}, 0, 0, level.title, cb_start_level, level.finished}};
        level_buttons.push_back(level_button);
        level_widget.attach(level_buttons[level_buttons.size() - 1]);
    }

    attach(level_widget); 
}