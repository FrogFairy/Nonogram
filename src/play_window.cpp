#include "play_window.h"
#include "rules_window.h"
#include "wrapper.h"

void Option_button::set_color()
{
    if (_active)
    {
        mark->set_color(active_color);
        mark->set_fill_color(active_color);
    }
    else
    {
        mark->set_color(default_color);
        mark->set_fill_color(default_color);
    }
}

Fill_button::Fill_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active)
    : Option_button{xy, w, h, label, cb, active}
{
    mark = std::make_unique<Graph_lib::Rectangle> (Graph_lib::Rectangle(Graph_lib::Point(xy.x + margin, xy.y + margin), w - margin * 2, h - margin * 2));
    mark->set_color(default_color);
    mark->set_fill_color(default_color);
}

Cross_button::Cross_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active)
    : Option_button{xy, w, h, label, cb, active}
{
    mark = std::make_unique<Graph_lib::Lines> (Graph_lib::Lines());

    ((Graph_lib::Lines*) mark.get())->add(Graph_lib::Point(xy.x + margin, xy.y + margin), Graph_lib::Point(xy.x + w - margin, xy.y + h - margin));
    ((Graph_lib::Lines*) mark.get())->add(Graph_lib::Point(xy.x + margin, xy.y + h - margin), Graph_lib::Point(xy.x + w - margin, xy.y + margin));

    mark->set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 3));
    mark->set_color(Graph_lib::Color::black);
}

Invert_button::Invert_button(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, bool active)
    : Option_button{xy, w, h, label, cb, active}
{
    default_color = Graph_lib::Color::no_color;
    active_color = Graph_lib::Color::black;

    label_widget = std::make_unique<Graph_lib::Label_widget> (Graph_lib::Label_widget(Graph_lib::Point(xy.x - 60, xy.y + 2 * margin), "invert:", 50, 20));

    mark = std::make_unique<Graph_lib::Lines> (Graph_lib::Lines());

    ((Graph_lib::Lines*) mark.get())->add(Graph_lib::Point(int(xy.x + 1.5 * margin), xy.y + int(h / 2) - margin), 
                                          Graph_lib::Point(int(xy.x + w / 2 - 0.5 * margin), xy.y + h - margin));
    ((Graph_lib::Lines*) mark.get())->add(Graph_lib::Point(int(xy.x + w / 2 - 0.5 * margin), xy.y + h - margin), 
                                          Graph_lib::Point(int(xy.x + w - 1.5 * margin), xy.y + margin));

    mark->set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 3));
    mark->set_color(Graph_lib::Color::black);
}

void Invert_button::attach(Graph_lib::Window& win)
{
    Option_button::attach(win);
    win.attach(*label_widget);
    label_widget->set_font_size(18);
}

Play_window::Play_window(Graph_lib::Point xy, int w, int h, const std::string& title, Level& level, Windows_wrapper &own)
    : Window_with_back{xy, w, h, title}, level{level}, own{own}, 
      rules_button{Graph_lib::Button{Graph_lib::Point{430, 10}, 40, 40, "?", cb_rules}},
      hint_button{Graph_lib::Point{480, 10}, 40, 40, "", cb_hint},
      lamp{Graph_lib::Point{483, 12}, "resources/hint.png"},
      restart_button{Graph_lib::Point{120, 10}, 100, 40, "restart", cb_restart},
      filled_button{Graph_lib::Point{295, 10}, 40, 40, "", cb_choose_option, true},
      cross_button{Graph_lib::Point{345, 10}, 40, 40, "", cb_choose_option, false},
      invert_button{Graph_lib::Point{x_max() - 50, y_max() - 50}, 40, 40, "", cb_invert, (level.inverted == Level::CROSS ? true : false)},
      button_option{Game_button::FILLED},
      board{Graph_lib::Point{40, 70}, x_max() - 80, y_max() - 140, level},
      hearts_img{}
{
    Window_with_back::size_range(w, h, w, h);
    
    int heart_size = 40, margin = 10;
    for (int i = 0; i < 3; ++i)
    {
        hearts_img.emplace_back(Heart{Graph_lib::Point(x_max() - (heart_size + margin) * (3 - i), 20), heart_size, heart_size, level.hearts_count - (2 - i) > 0});
    }
    
    for (int i = 0; i < hearts_img.size(); ++i)
        attach(hearts_img[i]);
        
    attach(rules_button);
    attach(hint_button);
    attach(lamp);
    attach(restart_button);
    attach(filled_button);
    attach(cross_button);
    attach(invert_button);
    attach(board);

    rules_button.set_font_size(18);
    restart_button.set_font_size(18);

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

void Play_window::cb_invert(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Fill_button*>(addr);
    static_cast<Play_window&>(pb->window()).invert();
}

void Play_window::invert()
{
    invert_button.change_state();
    invert_button.redraw();
    Level inv_level = board.invert_digits();
    own.db_levels.update_inverted(inv_level);
}


void Play_window::cb_choose_option(Graph_lib::Address, Graph_lib::Address addr)
{
    auto* pb = static_cast<Fill_button*>(addr);
    static_cast<Play_window&>(pb->window()).choose_option();
}

void Play_window::choose_option()
{
    filled_button.change_state();
    cross_button.change_state();

    filled_button.redraw();
    cross_button.redraw();

    if (filled_button.active())
        button_option = Game_button::FILLED;
    else
        button_option = Game_button::CROSS;
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