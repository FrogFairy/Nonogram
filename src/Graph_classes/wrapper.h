#ifndef WRAPPER_H
#define WRAPPER_H

#include <string>
#include <exception>

#include <Graph_lib/Window.h>
#include "main_window.h"
#include "../Logic_classes/database.h"
#include "play_window.h"
#include "rules_window.h"

struct Choose_level_window;
struct Generate_level_window;
struct Level_button;

struct Exit_exception {};

struct Windows_wrapper
{
  Windows_wrapper(Graph_lib::Point xy, int w, int h, const std::string &title)
    : xy{xy}, w{w}, h{h}, title{title}, main_win{new Main_window(xy, w, h, title, *this)}, db_levels{} 
    {};

  Database_levels db_levels;

  void open_generate_window();
  void open_choose_window(Size btn_label);
  void open_play_window(Size size, const std::string& level_title, Level_button& btn);
  void open_rules_window();

private:
  Main_window* main_win;
  Choose_level_window* choose_win;
  Generate_level_window* generate_win;
  Play_window* play_win;
  Rules_window* rul_win;

  Graph_lib::Point xy;
  int w, h;
  std::string title;
};

#endif // WRAPPER_H