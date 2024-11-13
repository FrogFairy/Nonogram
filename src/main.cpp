#include <iostream>

#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>

using namespace Graph_lib;

class Box : public Shape   
{
  public:
    Box(Point point, int height, int width, int radius)
      : m_point{point}, m_height{height}, m_width{width}, m_radius{radius}
    {};
  protected:
    void draw_lines() const override
    {
      fl_line(m_point.x + m_radius, m_point.y, m_point.x + m_width - m_radius, m_point.y);
      fl_line(m_point.x, m_point.y + m_radius, m_point.x, m_point.y + m_height - m_radius);
      fl_line(m_point.x + m_radius, m_point.y + m_height, m_point.x + m_width - m_radius, m_point.y + m_height);
      fl_line(m_point.x + m_width, m_point.y + m_radius, m_point.x + m_width, m_point.y + m_height - m_radius);
      fl_arc(m_point.x, m_point.y, 2*m_radius, 2*m_radius, 90, 180);
      fl_arc(m_point.x + m_width - 2* m_radius, m_point.y, 2*m_radius, 2*m_radius, 0, 90);
      fl_arc(m_point.x, m_point.y + m_height - 2* m_radius, 2*m_radius, 2*m_radius, -180, -90);
      fl_arc(m_point.x + m_width - 2* m_radius, m_point.y + m_height - 2* m_radius, 2*m_radius, 2*m_radius, -90, 0);

    }
  private:
    Point m_point;
    int m_height, m_width, m_radius;

};

class Arcc : public Shape
{
  public:
    Arcc(Point center, int radius, double a1, double a2) 
      :m_center{center}, m_radius{radius}, m_a1{a1}, m_a2{a2}
    {};

  protected:
    void draw_lines() const override 
    {
      fl_arc(m_center.x - m_radius, m_center.y - m_radius, 2*m_radius, 2*m_radius, m_a1, m_a2);
    }
  private:
    Point m_center;
    int m_radius;
    double m_a1, m_a2;
};


class CircleRecreated : public Shape
{
  public:
    CircleRecreated(Point center, int radius) 
      :m_center{center}, m_radius{radius}
    {};

  protected:
    void draw_lines() const override 
    {
      fl_arc(m_center.x - m_radius, m_center.y - m_radius, 2*m_radius, 2*m_radius, 0, 360);
    }
  private:
    Point m_center;
    int m_radius;
};

int main ()
try
{
  Point t1{100, 100};

  Simple_window win{t1, 600, 400, "Canvas"};

  Box box({win.x_max()/2, win.y_max()/2}, 100, 200, 30);

  win.attach(box);
  win.wait_for_button();
}
catch (std::exception& e)
{
  std::cerr << e.what() << std::endl;
  return 1;
}
catch (...)
{
  std::cerr << "Oops, something went wrong..." << std::endl;
  return 2;
}
