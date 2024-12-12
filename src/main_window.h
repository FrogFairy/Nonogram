#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <string>
#include <vector>

#include <Graph_lib/GUI.h>
#include <Graph_lib/Window.h>
#include "database.h"

struct Windows_wrapper;

struct Window_with_back : public Graph_lib::Window
{
  Window_with_back(Graph_lib::Point xy, int w, int h, const std::string& title)
      : Graph_lib::Window{xy, w, h, title}, back_button{Graph_lib::Point{10, y_max() - 30}, 100, 20, "back", cb_back} 
  {
    attach(back_button);
  }

  void wait_for_button()
  {
    while (!button_pushed && Fl::wait());
    button_pushed = false;
    Fl::redraw(); 
  }

  Graph_lib::Button back_button;
protected:
  bool button_pushed{false};
private:
  static void cb_back (Graph_lib::Address, Graph_lib::Address addr)
  {
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Window_with_back&>(pb->window()).back();
  }

  void back () { button_pushed = true; }
};

struct Size_button : public Graph_lib::Button
{
    Size_button(Graph_lib::Point p, int w, int h, Size size, Graph_lib::Callback cb)
        : Graph_lib::Button(p, w, h, to_string(size), cb), _level_size{size}
        {}

    void attach(Graph_lib::Window& win) { Graph_lib::Button::attach(win); }
    
    Size level_size() { return _level_size; }

private:
    Size _level_size;

};

struct Main_window : public Graph_lib::Window
{
public:
    Main_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper& own);

private:
    static void cb_go_to_level(Graph_lib::Address, Graph_lib::Address addr);
    static void cb_create_level(Graph_lib::Address, Graph_lib::Address addr);

    void go_to_level(Size btn_label);
    void create_level();

    std::vector<Size_button> size_buttons;

    Graph_lib::Menu main_widget;
    Windows_wrapper& own;
};

#endif // MAIN_WINDOWS_H