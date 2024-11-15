#ifndef MAIN_WINDOWS.H
#define MAIN_WINDOWS.H

#include <string>
#include <vector>

#include <Graph_lib/GUI.h>
#include <Graph_lib/Window.h>

struct Window_with_back : public Graph_lib::Window
{
  Window_with_back(Graph_lib::Point xy, int w, int h, const std::string& title)
      : Graph_lib::Window{xy, w, h, title}, back_button{Graph_lib::Point{10, y_max() - 30}, 100, 20, "Back", cb_back} 
      {
        attach(back_button);
      }

  void wait_for_button ()
  {
    while (!button_pushed && Fl::wait());
    button_pushed = false;
    Fl::redraw(); 
  }

  Graph_lib::Button back_button;

private:
  bool button_pushed{false};

  static void cb_back (Graph_lib::Address, Graph_lib::Address addr)  // callback 
  {
    auto* pb = static_cast<Graph_lib::Button*>(addr);
    static_cast<Window_with_back&>(pb->window()).back();
  }

  void back () { button_pushed = true; }
};

struct Main_window : public Graph_lib::Window
{
public:

    Main_window(Graph_lib::Point xy, int w, int h, const std::string &title);

    static void cb_go_to_level(Graph_lib::Address, Graph_lib::Address addr);
    static void cb_create_level(Graph_lib::Address, Graph_lib::Address addr);

    void go_to_level(std::string btn_label);
    void create_level();

private:
    Graph_lib::Menu main_widget;
    Graph_lib::Point p;
    int w;
    int h;
    std::string title;
};



#endif // MAIN_WINDOWS.H