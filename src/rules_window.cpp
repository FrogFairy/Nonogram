
#include "rules_window.h"
#include "wrapper.h"

Rules_window::Rules_window(Graph_lib::Point xy, int w, int h, const std::string &title, Windows_wrapper &own)
    : Window_with_back{xy, w, h, title}, own{own}, 
    rt{Graph_lib::Point{w/2-70, 40},"Rules"},
    rt_1{Graph_lib::Point{40, 90},"On each side of the grid (horizontally and vertically) there are numbers"},
    rt_2{Graph_lib::Point{40, 120},"that represent hints for filling the cells."},
    rt_3{Graph_lib::Point{40, 150}, "These numbers indicate how many consecutive colored cells should be"},
    rt_4{Graph_lib::Point{40, 180},"in the corresponding row or column. If there are several numbers,"},   
    rt_5{Graph_lib::Point{40, 210},"they are separated by at least one unpainted cell."}
{
    rt.set_font_size(30);

    rt_1.set_font_size(20);
    rt_2.set_font_size(20);
    rt_3.set_font_size(20);
    rt_4.set_font_size(20);
    rt_5.set_font_size(20);

    attach(rt);
    attach(rt_1);
    attach(rt_2);
    attach(rt_3);
    attach(rt_4);
    attach(rt_5);
}