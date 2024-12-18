#include <string>

#include "wrapper.h"
#include "choose_level.h"
#include "generate_level.h"

void Windows_wrapper::open_choose_window(Size btn_label)
{
    main_win->hide();
    choose_win = new Choose_level_window(xy, w, h, "Nonogram", btn_label, *this);
    choose_win->wait_for_button();
    if (!choose_win->shown())
    {
        delete choose_win;
        throw Exit_exception();
    }
    delete choose_win;
    main_win->show();
}

void Windows_wrapper::open_generate_window()
{
    main_win->hide();
    generate_win = new Generate_level_window(xy, w, h, "Nonogram", *this);
    generate_win->wait_for_button();
    if (!generate_win->shown())
    {
        delete generate_win;
        throw Exit_exception();
    }
    delete generate_win;
    main_win->show();
}

void Windows_wrapper::open_play_window(Size size, const std::string& level_title, Level_button& btn)
{
    choose_win->hide();

    Level level = db_levels.get_level(size, level_title);
    play_win = new Play_window(xy, w, h, "Nonogram", level, *this);
    play_win->wait_for_button();
    if (!play_win->shown())
    {
        delete play_win;
        throw Exit_exception();
    }
    delete play_win;

    level = db_levels.get_level(size, level_title);
    btn.change_color(level.finished);
    choose_win->show();
}

void Windows_wrapper::open_rules_window()
{
    play_win->hide();
    rul_win = new Rules_window(xy, w, h, "Nonogram", *this);
    rul_win->wait_for_button();
    if (!rul_win->shown())
    {
        delete rul_win;
        throw Exit_exception();
    }
    delete rul_win;
    play_win->show();
}