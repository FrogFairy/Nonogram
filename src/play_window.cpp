#include "play_window.h"
#include "rules_window.h"
#include "graph_board.h"
#include "wrapper.h"

Play_window::Play_window(Graph_lib::Point xy, int w, int h, const std::string& title, Level& level, Windows_wrapper &own)
    : Window_with_back{xy, w, h, title}, own{own}, rules_button{Graph_lib::Button{Graph_lib::Point{10, 10}, 40, 40, "?", cb_rules}},
      hint_button{Graph_lib::Point{60, 10}, 40, 40, "", cb_hint},
      lamp{Graph_lib::Point{63, 12}, "resources/hint.png"},
      restart_button{Graph_lib::Point{120, y_max() - 30}, 100, 20, "restart", cb_restart},
      fill_button{Graph_lib::Point{x_max() - 50, y_max() - 50}, 40, 40, "", cb_fill},
      cross_button{Graph_lib::Point{x_max() - 100, y_max() -50}, 40, 40, "", cb_cross},
      board{Graph_lib::Point{40, 70}, x_max() - 80, y_max() - 140, level},
      hearts_img{}
{
    hearts_img.push_back(new Graph_lib::Image(Graph_lib::Point(x_max() - 100, 20), "resources/heart.png"));
    hearts_img.push_back(new Graph_lib::Image(Graph_lib::Point(x_max() - 70, 20), "resources/heart.png"));
    hearts_img.push_back(new Graph_lib::Image(Graph_lib::Point(x_max() - 40, 20), "resources/heart.png"));
    
    for (int i = 0; i < hearts_img.size(); ++i)
        attach(hearts_img[i]);

    attach(rules_button);
    attach(hint_button);
    attach(lamp);
    attach(restart_button);
    attach(fill_button);
    attach(cross_button);
    attach(board);
}
      
void Play_window::rules()
{
    own.open_rules_window();
}

void Play_window::cb_rules(Graph_lib::Address, Graph_lib::Address addr)
{
    auto *pb = static_cast<Graph_lib::Button *>(addr);
    static_cast<Play_window &>(pb->window()).rules();
}
void Play_window::hint()
{
}
void Play_window::cb_hint(Graph_lib::Address, Graph_lib::Address addr)
{
}
void Play_window::restart()
{
}
void Play_window::cb_restart(Graph_lib::Address, Graph_lib::Address addr)
{
}

void Play_window::fill()
{
}
void Play_window::cb_fill(Graph_lib::Address, Graph_lib::Address addr)
{
}
void Play_window::cross()
{
}
void Play_window::cb_cross(Graph_lib::Address, Graph_lib::Address addr)
{
}
