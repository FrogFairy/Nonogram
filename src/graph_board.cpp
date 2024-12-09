#include "graph_board.h"
#include "play_window.h"
#include "wrapper.h"

void Game_button::init_mark()
{
    int margin = 5;
    switch (cur_state)
    {
        case EMPTY:
        {
            mark = nullptr;
            break;
        }
        case FILLED:
        case HINT_FILLED:
        case MISTAKE_FILLED:
        {
            mark = new Graph_lib::Rectangle(Graph_lib::Point(loc.x + margin, loc.y + margin), width - margin * 2, height - margin * 2);
            break;
        }
        default:
        {
            mark = new Graph_lib::Lines;
            ((Graph_lib::Lines*) mark)->add(Graph_lib::Point(loc.x + margin, loc.y + margin), Graph_lib::Point(loc.x + width - margin, loc.y + height - margin));
            ((Graph_lib::Lines*) mark)->add(Graph_lib::Point(loc.x + margin, loc.y + height - margin), Graph_lib::Point(loc.x + width - margin, loc.y + margin));
            mark->set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 3));
        }
    }

    if (!mark) return;

    Graph_lib::Color color = Graph_lib::Color::black;
    switch (cur_state)
    {
        case MISTAKE_CROSS:
        case MISTAKE_FILLED:
        {
            color = Graph_lib::Color::dark_red;
            break;
        }
        case HINT_CROSS:
        case HINT_FILLED:
            color = Graph_lib::Color::dark_green;
    }

    mark->set_color(color);
    mark->set_fill_color(color);

}

void Game_button::change_button(State state)
{
    cur_state = state;
    own->detach(*mark);
    delete mark;
    init_mark();

    if (mark)
        own->attach(*mark);
}

void Graph_board::init()
{
    int font_size = 20;
    int button_size = std::min((height - logic_board.max_cols * font_size) / logic_board.width, (width - logic_board.max_rows) / logic_board.height);
    int x_margin = width - button_size * logic_board.width;
    int y_margin = height - button_size * logic_board.height;

    for (int i = 0; i < logic_board.height; ++i)
    {
        Graph_lib::Vector_ref<Graph_lib::Text> r_digits;
        for (int j = 0; j < logic_board.width; ++j)
        {
            Game_button::State state = Game_button::State(logic_board.current[i][j]);
            switch (state)
            {
                case Game_button::HINT_CROSS:
                case Game_button::HINT_FILLED:
                {
                    logic_board.after_hint(std::vector<int> {i, j});
                    state = Game_button::State(logic_board.current[i][j]);
                    break;
                }

                case Game_button::MISTAKE_CROSS:
                case Game_button::MISTAKE_FILLED:
                {
                    logic_board.after_mistake(std::vector<int> {i, j});
                    state = Game_button::State(logic_board.current[i][j]);
                    break;
                }
            }

            auto button = new Game_button{Graph_lib::Point{loc.x + x_margin + j * button_size, loc.y + y_margin + i * button_size}, button_size, button_size, "", cb_click_button,
                                          i, j, state, *this};
            buttons.push_back(*button);

            if (j < logic_board.row_digits[i].size())
            {
                auto text = new Graph_lib::Text{Graph_lib::Point(0, 0), std::to_string(logic_board.row_digits[i][j])};
                Graph_lib::Point p{(int) (loc.x + x_margin - (logic_board.row_digits[i].size() - j) * font_size - font_size / 4 * text->length()), 
                                            loc.y + y_margin + i * button_size + std::max(button_size - font_size, font_size)};
                text->move(p.x, p.y);
                text->set_font_size(font_size);
                text->set_color(Graph_lib::Color::black);
                r_digits.push_back(*text);
            }
        }
        row_digits.push_back(r_digits);
    }

    for (int i = 0; i < logic_board.width; ++i)
    {
        Graph_lib::Vector_ref<Graph_lib::Text> c_digits;
        for (int j = 0; j < logic_board.col_digits[i].size(); ++j)
        {
            auto text = new Graph_lib::Text{Graph_lib::Point(0, 0), std::to_string(logic_board.col_digits[i][j])};
            Graph_lib::Point p{loc.x + x_margin + i * button_size + (button_size - font_size / 2 * text->length()) / 2, 
                                (int) (loc.y + y_margin - j * font_size - font_size / 2)};
            text->move(p.x, p.y);
            text->set_font_size(font_size);
            text->set_color(Graph_lib::Color::black);
            c_digits.push_back(*text);
        }
        col_digits.push_back(c_digits);
    }
}

void Graph_board::change_buttons()
{
    for (int i = 0; i < logic_board.height; ++i)
    {
        for (int j = 0; j < logic_board.width; ++j)
        {
            buttons[i * logic_board.height + j].change_button((Game_button::State) logic_board.current[i][j]);
            buttons[i * logic_board.height + j].block();
        }
    }
}

void Graph_board::redraw()
{
    for (int i = 0; i < buttons.size(); ++i)
        buttons[i].redraw();
}

void Graph_board::attach(Graph_lib::Window &win)
{ 
    for (int i = 0; i < buttons.size(); ++i)
    {
        win.attach(buttons[i]);
        if (i < row_digits.size())
        {
            for (int j = 0; j < row_digits[i].size(); ++j)
            {
                win.attach(row_digits[i][j]);
            }
        }
        if (i < col_digits.size())
            for (int j = 0; j < col_digits[i].size(); ++j)
            {
                win.attach(col_digits[i][j]);
            }
    }
    own = &win;
}

void Graph_board::block_buttons()
{
    blocked = !blocked;
    for (int i = 0; i < buttons.size(); ++i)
        buttons[i].block();
}

void Graph_board::change_previous()
{
    if (mistake.size())
    {
        logic_board.after_mistake(mistake);
        int x = mistake[0], y = mistake[1];
        Game_button& button = buttons[logic_board.height * x + y];
        button.change_button(logic_board.current[x][y] == 0 ? Game_button::CROSS : Game_button::FILLED);
        button.redraw();
        mistake = {};
    }
    else if (hint.size())
    {
        logic_board.after_hint(hint);
        int x = hint[0], y = hint[1];
        Game_button& button = buttons[logic_board.height * x + y];
        button.change_button(logic_board.current[x][y] == 0 ? Game_button::CROSS : Game_button::FILLED);
        button.redraw();
        hint = {};
    }
}

void Graph_board::get_hint()
{
    if (blocked) return;
    change_previous();
    Play_window* win = (Play_window*) own;

    std::vector<int> pos = logic_board.hint_click();
    int x = pos[0], y = pos[1];
    Game_button& btn = buttons[x * logic_board.height + y];

    auto state = (Game_button::State) logic_board.current[x][y];

    level.set_current(logic_board.current, logic_board.empty);
    win->update_current(level);

    if (logic_board.status == Logic_board::OK)
    {
        hint = {x, y};
        btn.change_button(state);
    }
    else if (logic_board.status == Logic_board::FINISH)
    {
        btn.change_button(state);
        level.set_finished(true);
        block_buttons();
        win->update_finished(level);
    }
    btn.redraw();
}

void Graph_board::cb_click_button(Graph_lib::Address, Graph_lib::Address addr)
{
    auto *pb = static_cast<Game_button*>(addr);
    (pb->board).click_button(pb);
}

void Graph_board::click_button(Game_button* btn)
{
    if (blocked || btn->state() != Game_button::EMPTY) return;
    change_previous();

    Play_window* win = (Play_window*) own;
    Game_button::State state = win->option();
    int x = btn->x(), y = btn->y();

    logic_board.set_click(x, y, state);
    level.set_current(logic_board.current, logic_board.empty);
    win->update_current(level);

    if (logic_board.status == Logic_board::OK)
        btn->change_button(state);

    else if (logic_board.status == Logic_board::FINISH)
    {
        btn->change_button(state);
        level.set_finished(true);
        block_buttons();
        win->update_finished(level);
    }
    
    else if (logic_board.status == Logic_board::MISTAKE)
    {
        mistake = {x, y};
        btn->change_button(logic_board.current[x][y] == 4 ? Game_button::MISTAKE_CROSS : Game_button::MISTAKE_FILLED);
        level.set_hearts(level.hearts_count - 1);
        if (level.hearts_count == 0) block_buttons();
        win->update_heart_count(level);
    }
}