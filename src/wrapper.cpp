#include <string>

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

void Windows_wrapper::open_play_window(const std::string& size, const std::string& level_title)
{
    choose_win->hide();
    Level level = db_levels.get_level(size, level_title);
    play_win = new Play_window(xy, w, h, "Play window", level, *this);
    play_win->wait_for_button();
    if (!play_win->shown())
        exit(0);
    delete play_win;
    // choose_win->update_level(level);
    choose_win->show();
}

void Windows_wrapper::open_rules_window()
{
    play_win->hide();
    rul_win = new Rules_window(xy, w, h, "Rules window", *this);
    rul_win->wait_for_button();
    if (!rul_win->shown())
        exit(0);
    delete rul_win;
    play_win->show();
}