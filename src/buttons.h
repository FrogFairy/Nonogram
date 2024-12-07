#ifndef BUTTONS_H
#define BUTTONS_H

#include <Graph_lib/GUI.h>
#include <Graph_lib/Window.h>
#include <Graph_lib/Graph.h>

struct Game_Button : Graph_lib::Widget
{
public:
    Game_Button(Graph_lib::Point xy, int w, int h, const std::string &label, Graph_lib::Callback cb, int is_fill) : Widget{xy, w, h, label, cb} {}
    void attach(Window &);

    void change_button();
    void change_color();

private:

};

class Fill_Button : public Graph_lib::Button
{
public:
    Fill_Button(Graph_lib::Point xy, int w, int h, std::string label, Graph_lib::Callback cb): Button{xy, w, h, label, cb} {}

   

    void attach(Graph_lib::Window& win) override
  {
    Button::attach(win);
    pw->color(Graph_lib::Color::black);
  }

    void wait_for_button ()
   {
    while (!button_pushed && Fl::wait())
      ;
    button_pushed = false;
    Fl::redraw(); 
   }

protected:
   bool button_pushed{false};
   static void cb(Graph_lib::Address, Graph_lib::Address addr)
   {
   }

   void change_color()
   {
       // if (database.label.flag)
       {
           pw->color(Graph_lib::Color::green);
       }
   }
};


#endif // BUTTONS_H