#ifndef WIDGETS_H
#define WIDGETS_H

#include <string>

#include <Graph_lib/Graph.h>
#include <Graph_lib/GUI.h>

struct Widget_with_back : public Graph_lib::Widget
{
  Widget_with_back(Graph_lib::Point xy, int w, int h, const std::string& title, Graph_lib::Callback cb)
      : Graph_lib::Widget {xy, w, h, title, nullptr}, back_button{Graph_lib::Point{xy.x + 10, xy.y + h - 10}, 70, 20, "Back", cb}
  {}

  void show ()
  {
    back_button.show();
  }

  void hide ()
  {
    back_button.hide();
  }

  void move (int dx, int dy)
  {
    back_button.move(dx, dy);
  }

  void attach (Graph_lib::Window& win)
  {
      win.attach(back_button);
      own = &win;
  }

  Graph_lib::Button back_button;
};

struct Main_widget : public Graph_lib::Widget
{
    Main_widget(Graph_lib::Point xy, int w, int h, const std::string& label) 
    : Widget{xy, w, h, label, nullptr}, levels_menu{xy, w, h, Graph_lib::Menu::vertical, label}
    {};

    void show ()  // show all buttons
    {
        levels_menu.show();
    }

    void hide ()  // hide all buttons
    {
        levels_menu.hide();
    }

    void move (int dx, int dy)  // move all buttons
    {
        levels_menu.move(dx, dy);
    }
    
    void attach (Graph_lib::Button& b)
    {
        levels_menu.attach(b);
    }
    void attach (Graph_lib::Button* b)
    {
        attach(*b);
    }

    void attach (Graph_lib::Window& win)  // attach all buttons
    {
        win.attach(levels_menu);
        own = &win;
    }

    // Graph_lib::Vector_ref<Graph_lib::Widget> widgets;
    Graph_lib::Menu levels_menu;
};

#endif //WIDGETS_H
