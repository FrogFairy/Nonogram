#ifndef WRAPPER.H
#define WRAPPER.H

#include <string>

#include <Graph_lib/Window.h>
#include "main_window.h"

struct Choose_level_window;
struct Generate_level_window;

struct Windows_wrapper
{
  Windows_wrapper(Graph_lib::Point xy, int w, int h, const std::string &title)
    : xy{xy}, w{w}, h{h}, title{title}, main_win{new Main_window(xy, w, h, title, *this)} {};

  void open_generate_window();
  void open_choose_window(const std::string& btn_label);
  void open_play_window(const std::string& size, const std::string& level_title);
private:
  Main_window* main_win;
  Choose_level_window* choose_win;
  Generate_level_window* generate_win;
  Window_with_back* win_back; // заменить на окно с уровнем
  Graph_lib::Point xy;
  int w, h;
  std::string title;
};

#endif // WRAPPER.H