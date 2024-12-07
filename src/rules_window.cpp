
#include "rules_window.h"
#include "wrapper.h"

Rules_window::Rules_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper &own)
    : Window_with_back{xy, w, h, title}, own{own},
      rt{Graph_lib::Point{(x_max() - 70) / 2, 40}, "Rules"},
      rules{Graph_lib::Point{80, 50}, "resources/rules.png"}
{
    rt.set_font_size(30);

   
    attach(rules);
    attach(rt);
}