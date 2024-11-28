#include <string>
#include <iostream>

#include "wrapper.h"
#include "choose_level.h"
#include "generate_level.h"

void Windows_wrapper::open_choose_window(const std::string& btn_label)
{
    main_win->hide();
    choose_win = new Choose_level_window(xy, w, h, "Choice level", btn_label, *this);
    choose_win->wait_for_button();
    if (!choose_win->shown())
        exit(0);
    delete choose_win;
    main_win->show();
}

void Windows_wrapper::open_play_window(const std::string& size, const std::string& level_title)
{
    choose_win->hide();
    win_back = new Window_with_back(xy, w, h, level_title); // заменить на окно с уровнем
    win_back->wait_for_button();
    if (!win_back->shown())
        exit(0);
    delete win_back;
    choose_win->show();
}

void Windows_wrapper::open_generate_window()
{
    main_win->hide();
    generate_win = new Generate_level_window(xy, w, h, "Create level", *this);
    generate_win->wait_for_button();
    if (!generate_win->shown())
        exit(0);
    delete generate_win;
    main_win->show();
}