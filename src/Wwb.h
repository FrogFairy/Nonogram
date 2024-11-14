#ifndef WWB_H
#define WWB_H
#include <iostream>
#include <string>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
#include <Graph_lib/Window.h>
#include <Graph_lib/GUI.h>

using namespace Graph_lib;

struct Window_with_back : Window
{
  Window_with_back(Point xy, int w, int h, const std::string& title, const Fl_Window& last_win)
      : Window{xy, w, h, title}, back_button{Point{xy.x+10, xy.y+h-10}, 70, 20, "Back", cb_back}
  {
    attach(back_button);
  }

  void wait_for_button ()

  {
    while (!button_pushed && Fl::wait())
      ;
    button_pushed = false;
    Fl::redraw(); 
  }

  Button back_button;

private:
  bool button_pushed{false};

  static void cb_back (Address, Address addr)  // callback 
  {
    /*auto* pb = static_cast<Button*>(addr);
    static_cast<Window_with_back&>(pb->window()).back();*/

    Fl_Window(&last_win());
  }

  void back () { button_pushed = true; }
};
#endif //WWB_H
