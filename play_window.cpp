#include "play_window.h"
#include "rules_window.h"
#include "graph_board.h"
#include "wrapper.h"

Play_window::Play_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper &own)
    : Window_with_back{xy, w, h, title}, own{own}, rules_button{Graph_lib::Button{Graph_lib::Point{10, 10}, 40, 40, "?", cb_rules}},
      hint_button{Graph_lib::Point{60, 10}, 40, 40, "", cb_hint},
      lamp{Graph_lib::Point{62, 10}, "resources/hint.png"},
      restart_button{Graph_lib::Point{120, y_max() - 30}, 100, 20, "restart", cb_restart}
// board{Graph_lib::Point{100, 100}, 200, 200, 10, 10}
{
    // Graph_lib::Button fill_button{Graph_lib::Point{10,10}, 10, 10, "", cb_fill};
    // Graph_lib::Button cross_button{Graph_lib::Point{10,10}, 10, 10, "1", cb_cross};

    //Graph_lib::Vector_ref<Graph_lib::Image> hearts_img;
    //Graph_board board{Graph_lib::Point{200, 100}, int n, int button_size};

    attach(rules_button);
    attach(hint_button);
    attach(lamp);
    attach(restart_button);
    // attach(fill_button);
    // attach(cross_button);
    //attach(board);
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

// void Play_window::fill()
// {
//     Play_window win{xy, w, h, title};
//     this->hide();
//     win.wait_for_button();
//     this->show();
// }
// void Play_window::cb_fill(Graph_lib::Address, Graph_lib::Address addr)
// {
//     auto *pb = static_cast<Graph_lib::Button *>(addr);
//     static_cast<Play_window &>(pb->window()).fill(pb->label);
// }
// void Play_window::cross()
// {
//     Play_window win{xy, w, h, title};
//     this->hide();
//     win.wait_for_button();
//     this->show();
// }
// void Play_window::cb_cross(Graph_lib::Address, Graph_lib::Address addr)
// {
//     auto *pb = static_cast<Graph_lib::Button *>(addr);
//     static_cast<Play_window &>(pb->window()).cross(pb->label);
// }
