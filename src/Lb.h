#ifndef LB_H
#define LB_H
#include <iostream>
#include <string>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
#include <Graph_lib/Window.h>
#include <Graph_lib/GUI.h>

using namespace Graph_lib;

class Level_button: public Button
{
    Level_button(Point xy, const std::string& name_of_level): Button{xy, B_w, B_h, name_of_level, cb};

    constexpr static int B_h = 20;

    constexpr static int B_w = 200;

    void attach(Graph_lib::Window& win) override
  {
    Button::attach(win);
    if (!pw) error("Cell is not attrached to a window");
    pw->color(Color::white);
  }

    void wait_for_button ()
   {
    while (!button_pushed && Fl::wait())
      ;
    button_pushed = false;
    Fl::redraw(); 
   }

  Button l_button;
    protected:
        bool button_pushed{false};
        static void cb (Address, Address addr)
        {
            start_level(name_of_level);
        }

        void change_color()
        {
            //if (database.label.flag)
            { 
                pw->color(Color::green);
            }
                
        }

    

};

#endif //LB_H
