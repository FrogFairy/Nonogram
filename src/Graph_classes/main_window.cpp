#include "main_window.h"
#include "wrapper.h"
#include "../Logic_classes/database.h"
#include "constants.h"

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

Main_window::Main_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper &own)
    : Graph_lib::Window{xy, w, h, title}, own{own},
      main_widget{main_widget_point, main_widget_width, main_widget_height, Graph_lib::Menu::vertical, "widget_for_main_window"},
      generate_button{Graph_lib::Point{0, 0}, 0, 0, "Generate level", cb_create_level}
{
    Graph_lib::Window::size_range(w, h, w, h);

    for (unsigned int i = 10; i < 30; i += 5)
    {
        size_buttons.push_back(Size_button{Graph_lib::Point{0, 0}, 0, 0, Size{i, i}, cb_go_to_level});
    }

    main_widget.attach(generate_button);

    for (int i = 0; i < size_buttons.size(); ++i)
    {
        main_widget.attach(size_buttons[i]);
    }

    attach(main_widget);
    main_widget.set_font_size(m_win_text_size);
}

