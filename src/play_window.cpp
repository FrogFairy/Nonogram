#include "play_window.h"
#include "rules_window.h"
#include "wrapper.h"

Fill_button::Fill_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active, Button_type b_type)
                : Graph_lib::Button{xy, w, h, label, cb}, _active{active} 
{
    int margin = 5;
    if (b_type == Button_type::FILLED)
    {
        mark = new Graph_lib::Rectangle(Graph_lib::Point(xy.x + margin, xy.y + margin), w - margin * 2, h - margin * 2);
    }
    else
    {
        mark = new Graph_lib::Lines;
        ((Graph_lib::Lines*) mark)->add(Graph_lib::Point(xy.x + margin, xy.y + margin), Graph_lib::Point(xy.x + w - margin, xy.y + h - margin));
        ((Graph_lib::Lines*) mark)->add(Graph_lib::Point(xy.x + margin, xy.y + h - margin), Graph_lib::Point(xy.x + w - margin, xy.y + margin));
        mark->set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 3));
    }
    mark->set_color(Graph_lib::Color::black);
    mark->set_fill_color(Graph_lib::Color::black);
}

void Fill_button::set_color()
{
    if (_active)
    {
        pw->color(Graph_lib::Color::dark_green);
        pw->color2(Graph_lib::Color::dark_green);
    }
    else
    {
        pw->color(Graph_lib::Color::no_color);
        pw->color2(Graph_lib::Color::no_color);
    }
}

Play_window::Play_window(Graph_lib::Point xy, int w, int h, const std::string& title, Level& level, Windows_wrapper &own)
    : Window_with_back{xy, w, h, title}, level{level}, own{own}, 
      rules_button{Graph_lib::Button{Graph_lib::Point{10, 10}, 40, 40, "?", cb_rules}},
      hint_button{Graph_lib::Point{60, 10}, 40, 40, "", cb_hint},
      lamp{Graph_lib::Point{63, 12}, "resources/hint.png"},
      restart_button{Graph_lib::Point{120, y_max() - 30}, 100, 20, "restart", cb_restart},
      filled_button{Graph_lib::Point{x_max() - 50, y_max() - 50}, 40, 40, "", cb_choose_option, true, Fill_button::FILLED},
      cross_button{Graph_lib::Point{x_max() - 100, y_max() - 50}, 40, 40, "", cb_choose_option, false, Fill_button::CROSS},
      button_option{Game_button::FILLED},
      board{Graph_lib::Point{40, 70}, x_max() - 80, y_max() - 140, level},
      hearts_img{}
{
    Window_with_back::size_range(w, h, w, h);
    
    int heart_size = 40, margin = 10;
    for (int i = 0; i < 3; ++i)
        hearts_img.push_back(Heart{Graph_lib::Point(x_max() - (heart_size + margin) * (3 - i), 20), heart_size, heart_size, level.hearts_count - (2 - i) > 0});
    
    for (int i = 0; i < hearts_img.size(); ++i)
        attach(hearts_img[i]);

    attach(rules_button);
    attach(hint_button);
    attach(lamp);
    attach(restart_button);
    attach(filled_button);
    attach(cross_button);
    attach(board);

    if (level.finished)
        fl_alert(text_finish.c_str());
    else if (level.hearts_count == 0)
        fl_alert(text_hearts.c_str());
}

void Play_window::cb_rules(Graph_lib::Address, Graph_lib::Address addr)
{
    auto *pb = static_cast<Graph_lib::Button *>(addr);
    static_cast<Play_window &>(pb->window()).rules();
}

void Play_window::rules()
{
    own.open_rules_window();
}

void Play_window::cb_hint(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Play_window&>(pb->window()).hint();
}

void Play_window::hint()
{
    board.get_hint();
}

void Play_window::cb_restart(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Play_window&>(pb->window()).restart();
}

void Play_window::restart()
{
    level.restart();

    board.restart();
    board.redraw();

    for (int i = 0; i < hearts_img.size(); ++i)
    {
        detach(hearts_img[i]);
        hearts_img[i].change(true);
        attach(hearts_img[i]);
    }

    own.db_levels.update_level(level);
}


void Play_window::cb_choose_option(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Fill_button*>(addr);
    static_cast<Play_window&>(pb->window()).choose_option();
}

void Play_window::choose_option()
{
    filled_button.change_color();
    cross_button.change_color();

    filled_button.redraw();
    cross_button.redraw();

    if (filled_button.active())
        button_option = Game_button::FILLED;
    else
        button_option = Game_button::CROSS;
}

void Play_window::update_hidden_rows(Level& level)
{
    own.db_levels.update_hidden_rows(level);
}

void Play_window::update_hidden_cols(Level& level)
{
    own.db_levels.update_hidden_cols(level);
}

void Play_window::update_current(Level& level)
{
    own.db_levels.update_current(level);
}

void Play_window::update_finished(Level& level)
{
    own.db_levels.update_finished(level);
    fl_alert(text_finish.c_str());
}

void Play_window::update_heart_count(Level& level)
{
    for (int i = 0; i < hearts_img.size(); ++i)
    {
        if (hearts_img[i].is_filled())
        {
            detach(hearts_img[i]);
            hearts_img[i].change(false);
            attach(hearts_img[i]);
            break;
        }
    }

    own.db_levels.update_heart_count(level);
    if (board.is_blocked())
        fl_alert(text_hearts.c_str());
}