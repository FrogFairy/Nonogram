#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Graph_lib/Graph.h>
#include <Graph_lib/GUI.h>

constexpr Fl_Color default_color = FL_BACKGROUND_COLOR;
constexpr Graph_lib::Color::Color_type black = Graph_lib::Color::black;
constexpr Graph_lib::Color::Color_type no_color = Graph_lib::Color::no_color;
constexpr Graph_lib::Color::Color_type white = Graph_lib::Color::white;
constexpr Graph_lib::Color::Color_type red = Graph_lib::Color::red;
constexpr Graph_lib::Color::Color_type dark_red = Graph_lib::Color::dark_red;
constexpr Graph_lib::Color::Color_type dark_green = Graph_lib::Color::dark_green;

constexpr Graph_lib::Point window_point = Graph_lib::Point{400, 100};
const int window_width = 700;
const int window_height = 700;

constexpr int p_win_button_h = 40;
constexpr int p_win_button_w = 40;

constexpr int m_win_button_h = 50;
constexpr int m_win_button_w = 200;

constexpr int text_size = 18;
constexpr int gen_lvl_text_size = text_size;
constexpr int chs_lvl_text_size = text_size;
constexpr int p_win_text_size = text_size;
constexpr int board_text_size = text_size;
constexpr int m_win_text_size = text_size;
constexpr int rules_text_size = 30;

constexpr double mark_margin = 0.05;

constexpr int heart_size = 40;
constexpr int heart_margin = 10;

constexpr Graph_lib::Point level_widget_point = Graph_lib::Point{260, 250};
constexpr int level_widget_width = m_win_button_w;
constexpr int level_widget_height = m_win_button_h;

constexpr Graph_lib::Point scroll_widget_point = Graph_lib::Point{0, 250};

constexpr Graph_lib::Point size_box_point = Graph_lib::Point{260, 250};
constexpr int size_box_width = m_win_button_w;
constexpr int size_box_height = m_win_button_h;

constexpr Graph_lib::Point image_chooser_point = Graph_lib::Point{260, 325};
constexpr int image_chooser_width = m_win_button_w;
constexpr int image_chooser_height = m_win_button_h;

constexpr Graph_lib::Point level_name_point = Graph_lib::Point{260, 400};
constexpr int level_name_width = m_win_button_w;
constexpr int level_name_height = m_win_button_h;

constexpr Graph_lib::Point save_button_point = Graph_lib::Point{590, 630};
constexpr int save_button_width = 100;
constexpr int save_button_height = 40;

constexpr double r_koeff = 0.2125;
constexpr double g_koeff = 0.7154;
constexpr double b_koeff = 0.0721;

const Graph_lib::Point main_widget_point = Graph_lib::Point{int((window_width - 200) / 2), int((window_height - ((30 - 10) / 5 + 1) * 50 - (30 - 10) / 5 * 20) / 2)};
constexpr int main_widget_width = m_win_button_w;
constexpr int main_widget_height = m_win_button_h;

constexpr Graph_lib::Point rules_button_point = Graph_lib::Point{430, 10};
constexpr int rules_button_width = p_win_button_w;
constexpr int rules_button_height = p_win_button_h;

constexpr Graph_lib::Point hint_button_point = Graph_lib::Point{480, 10};
constexpr int hint_button_width = p_win_button_w;
constexpr int hint_button_height = p_win_button_h;

constexpr Graph_lib::Point lamp_point = Graph_lib::Point{483, 12};

constexpr Graph_lib::Point restart_button_point = Graph_lib::Point{120, 10};
constexpr int restart_button_width = 100;
constexpr int restart_button_height = p_win_button_h;

constexpr Graph_lib::Point filled_button_point = Graph_lib::Point{295, 10};
constexpr int filled_button_width = p_win_button_w;
constexpr int filled_button_height = p_win_button_h;

constexpr Graph_lib::Point cross_button_point = Graph_lib::Point{345, 10};
constexpr int cross_button_width = p_win_button_w;
constexpr int cross_button_height = p_win_button_h;

const Graph_lib::Point invert_button_point = Graph_lib::Point{window_width - 50, window_height - 50};
constexpr int invert_button_width = p_win_button_w;
constexpr int invert_button_height = p_win_button_h;

constexpr Graph_lib::Point board_point = Graph_lib::Point{40, 70};
const int board_width = window_width - 80;
const int board_height = window_height - 140;


const Graph_lib::Point rules_text_point = Graph_lib::Point{(window_width - 70) / 2, 40};

constexpr Graph_lib::Point rules_point = Graph_lib::Point {80, 50};

#endif // CONSTANTS_H