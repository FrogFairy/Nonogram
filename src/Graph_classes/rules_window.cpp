
#include "rules_window.h"
#include "wrapper.h"
#include "constants.h"

Rules_window::Rules_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper &own)
    : Window_with_back{xy, w, h, title}, own{own},
      rt{rules_text_point, "Rules"},
      rules{rules_point, "resources/rules.png"}
{
    Window_with_back::size_range(w, h, w, h);
    rt.set_font_size(rules_text_size);

    attach(rules);
    attach(rt);
}