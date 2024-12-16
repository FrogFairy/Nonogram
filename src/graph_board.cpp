#include "graph_board.h"
#include "play_window.h"
#include "wrapper.h"

void Game_button::init_mark()
{
    int margin = width * 0.05;
    switch (cur_state)
    {
        case Level::EMPTY:
        {
            mark = nullptr;
            break;
        }
        case Level::FILLED:
        case Level::HINT_FILLED:
        case Level::MISTAKE_FILLED:
        {
            mark = new Graph_lib::Rectangle(Graph_lib::Point(int(loc.x + margin), int(loc.y + margin)), int(width - margin * 2), int(height - margin * 2));
            break;
        }
        default:
        {
            mark = new Graph_lib::Lines;
            ((Graph_lib::Lines*) mark)->add(Graph_lib::Point(int(loc.x + margin), int(loc.y + margin)), Graph_lib::Point(int(loc.x + width - margin), int(loc.y + height - margin)));
            ((Graph_lib::Lines*) mark)->add(Graph_lib::Point(int(loc.x + margin), int(loc.y + height - margin)), Graph_lib::Point(int(loc.x + width - margin), int(loc.y + margin)));
            mark->set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 3));
        }
    }

    if (!mark) return;

    Graph_lib::Color color = Graph_lib::Color::black;
    switch (cur_state)
    {
        case Level::MISTAKE_CROSS:
        case Level::MISTAKE_FILLED:
        {
            color = Graph_lib::Color::dark_red;
            break;
        }
        case Level::HINT_CROSS:
        case Level::HINT_FILLED:
            color = Graph_lib::Color::dark_green;
    }

    mark->set_color(color);
    mark->set_fill_color(color);
}

void Game_button::change_button(Level::Cell_state state)
{
    cur_state = state;
    own->detach(*mark);
    delete mark;
    init_mark();

    if (mark)
        own->attach(*mark);
}

void Graph_board::init_buttons()
{
    buttons = {};

    int font_size = 18;
    int font_width = Graph_lib::font_width(font_size);
    int font_height = Graph_lib::font_height(font_size);

    int button_size = std::min((height - logic_board.max_cols() * font_height) / logic_board.height(), 
                                (width - logic_board.max_rows() * font_width) / logic_board.width());
    int x_margin = width - button_size * logic_board.width();
    int y_margin = height - button_size * logic_board.height();

    for (int i = 0; i < logic_board.height(); ++i)
    {
        for (int j = 0; j < logic_board.width(); ++j)
        {
            Level::Cell_state state = Level::Cell_state(logic_board.current()[i][j]);
            switch (state)
            {
                case Level::HINT_CROSS:
                case Level::HINT_FILLED:
                {
                    logic_board.after_hint(Position {i, j});
                    state = Level::Cell_state(logic_board.current()[i][j]);
                    break;
                }

                case Level::MISTAKE_CROSS:
                case Level::MISTAKE_FILLED:
                {
                    logic_board.after_mistake(Position {i, j});
                    state = Level::Cell_state(logic_board.current()[i][j]);
                    break;
                }
            }

            auto button = new Game_button{Graph_lib::Point{loc.x + x_margin + j * button_size, loc.y + y_margin + i * button_size}, button_size, button_size, "", cb_click_button,
                                          i, j, state, *this};
            buttons.push_back(*button);
        }
    }
}

void Graph_board::init_digits()
{
    row_digits = {};
    col_digits = {};

    int font_size = 18;
    int font_width = Graph_lib::font_width(font_size);
    int font_height = Graph_lib::font_height(font_size);

    int button_size = std::min((height - logic_board.max_cols() * font_height) / logic_board.height(), 
                                (width - logic_board.max_rows() * font_width) / logic_board.width());
    int x_margin = width - button_size * logic_board.width();
    int y_margin = height - button_size * logic_board.height();

    auto hidden_rows = logic_board.hidden_rows();
    auto row_intervals = logic_board.row_intervals();

    for (int i = 0; i < row_intervals.size(); ++i)
    {
        Graph_lib::Vector_ref<Graph_lib::Text> r_digits;
        for (int j = 0; j < row_intervals[i].size(); ++j)
        {
            std::string value = "0";
            if (!row_intervals[i][j].empty())
                value = std::to_string(row_intervals[i][j].end - row_intervals[i][j].start + 1);

            auto text = new Graph_lib::Text{Graph_lib::Point(0, 0), value};
            auto color = (std::find(hidden_rows.begin(), hidden_rows.end(), Position {i, j}) == hidden_rows.end() ? 
                                    Graph_lib::Color::black : Graph_lib::Color::white);
            Graph_lib::Point p{(int) (loc.x + x_margin - 3 * (row_intervals[i].size() - j) * font_width), 
                        loc.y + y_margin + i * button_size + int(button_size / 2) + int(font_height / 2)};
            text->move(p.x, p.y);
            text->set_font_size(font_size);
            text->set_color(color);
            r_digits.push_back(*text);
        }
        row_digits.push_back(r_digits);
    }

    auto hidden_cols = logic_board.hidden_cols();
    auto col_intervals = logic_board.col_intervals();

    for (int i = 0; i < col_intervals.size(); ++i)
    {
        Graph_lib::Vector_ref<Graph_lib::Text> c_digits;
        for (int j = 0; j < col_intervals[i].size(); ++j)
        {
            std::string value = "0";
            if (!col_intervals[i][j].empty())
                value = std::to_string(col_intervals[i][j].end - col_intervals[i][j].start + 1);

            auto text = new Graph_lib::Text{Graph_lib::Point(0, 0), value};
            auto color = (std::find(hidden_cols.begin(), hidden_cols.end(), Position {i, j}) == hidden_cols.end() ? 
                                        Graph_lib::Color::black : Graph_lib::Color::white);
            Graph_lib::Point p{loc.x + x_margin + i * button_size + int(button_size / 2) - int(font_width / 2), 
                            (int) (loc.y + y_margin - j * font_height - font_height / 2)};

            text->move(p.x, p.y);
            text->set_font_size(font_size);
            text->set_color(color);
            c_digits.push_back(*text);
        }
        col_digits.push_back(c_digits);
    }
}

Level Graph_board::invert_digits()
{
    level.inverted = (level.inverted == Level::FILLED_VAL ? Level::CROSS_VAL : Level::FILLED_VAL);
    logic_board.invert();

    detach_digits();
    init_digits();
    attach_digits(*own);

    own->redraw();

    return level;
}

void Graph_board::change_buttons(bool state)
{
    for (int i = 0; i < logic_board.height(); ++i)
    {
        for (int j = 0; j < logic_board.width(); ++j)
        {
            buttons[i * logic_board.height() + j].change_button((Level::Cell_state) logic_board.current()[i][j]);
            buttons[i * logic_board.height() + j].block(state);
        }
    }
}

void Graph_board::redraw()
{
    for (int i = 0; i < buttons.size(); ++i)
        buttons[i].redraw();
    
    auto hidden_rows = logic_board.hidden_rows();
    auto hidden_cols = logic_board.hidden_cols();
    for (int i = 0; i < row_digits.size(); ++i)
    {
        for (int j = 0; j < row_digits[i].size(); ++j)
        {
            auto color = (std::find(hidden_rows.begin(), hidden_rows.end(), Position {i, j}) == hidden_rows.end() ? 
                                        Graph_lib::Color::black : Graph_lib::Color::white);
            set_digit_color(row_digits[i][j], color);
        }
    }

    for (int i = 0; i < col_digits.size(); ++i)
    {
        for (int j = 0; j < col_digits[i].size(); ++j)
        {
            auto color = (std::find(hidden_cols.begin(), hidden_cols.end(), Position {i, j}) == hidden_cols.end() ? 
                                        Graph_lib::Color::black : Graph_lib::Color::white);
            set_digit_color(col_digits[i][j], color);
        }
    }

    // win->redraw();
}

void Graph_board::attach(Graph_lib::Window &win)
{
    for (int i = 0; i < buttons.size(); ++i)
    {
        win.attach(buttons[i]);
    }
    attach_digits(win);
    own = &win;
}

void Graph_board::detach()
{
    for (int i = 0; i < buttons.size(); ++i)
    {
        own->attach(buttons[i]);
    }
    detach_digits();
}

void Graph_board::attach_digits(Graph_lib::Window& win)
{
    for (int i = 0; i < row_digits.size(); ++i)
    {
        for (int j = 0; j < row_digits[i].size(); ++j)
        {
            win.attach(row_digits[i][j]);
        }
    }

    for (int i = 0; i < col_digits.size(); ++i)
    {
        for (int j = 0; j < col_digits[i].size(); ++j)
        {
            win.attach(col_digits[i][j]);
        }
    }
}

void Graph_board::detach_digits()
{
    for (int i = 0; i < row_digits.size(); ++i)
    {
        for (int j = 0; j < row_digits[i].size(); ++j)
        {
            own->detach(row_digits[i][j]);
        }
    }

    for (int i = 0; i < col_digits.size(); ++i)
    {
        for (int j = 0; j < col_digits[i].size(); ++j)
        {
            own->detach(col_digits[i][j]);
        }
    }
}

void Graph_board::block_buttons(bool state)
{
    blocked = state;
    for (int i = 0; i < buttons.size(); ++i)
        buttons[i].block(state);
}

void Graph_board::change_previous()
{
    if (!mistake.empty())
    {
        logic_board.after_mistake(mistake);
        int x = mistake.x, y = mistake.y;
        Game_button& button = buttons[logic_board.height() * x + y];
        button.change_button(logic_board.current()[x][y] == 0 ? Level::CROSS : Level::FILLED);
        button.redraw();
        mistake = {};
    }
    else if (!hint.empty())
    {
        logic_board.after_hint(hint);
        int x = hint.x, y = hint.y;
        Game_button& button = buttons[logic_board.height() * x + y];
        button.change_button(logic_board.current()[x][y] == 0 ? Level::CROSS : Level::FILLED);
        button.redraw();
        hint = {};
    }
}

void Graph_board::set_digit_color(Graph_lib::Text& text, Graph_lib::Color color)
{
    own->detach(text);
    text.set_color(color);
    own->attach(text);
}

void Graph_board::change_digits(Position pos)
{
    std::vector<Position> pos_needful_digits = logic_board.changed_digits(pos, level.inverted);

    if (!pos_needful_digits[0].empty())
    {
        Graph_lib::Text& text = row_digits[pos_needful_digits[0].x][pos_needful_digits[0].y];
        set_digit_color(text, Graph_lib::Color::white);
        
        // text.draw();
        own->redraw();
    }
    if (!pos_needful_digits[1].empty())
    {
        Graph_lib::Text& text = col_digits[pos_needful_digits[1].x][pos_needful_digits[1].y];
        set_digit_color(text, Graph_lib::Color::white);

        // text.draw();
        own->redraw();
    }

    logic_board.changed_digits(pos, level.inverted == Level::FILLED_VAL ? Level::CROSS_VAL : Level::FILLED_VAL);
}

void Graph_board::get_hint()
{
    if (blocked) return;
    change_previous();
    Play_window* win = (Play_window*) own;

    Position pos = logic_board.hint_click();
    int x = pos.x, y = pos.y;
    Game_button& btn = buttons[x * logic_board.height() + y];

    auto state = (Level::Cell_state) logic_board.current()[x][y];

    auto current = logic_board.current();
    auto empty = logic_board.get_empty();
    level.set_current(current, empty);
    win->update_current(level);

    change_digits(Position {x, y});

    if (logic_board.status() == Logic_board::OK)
    {
        hint = {x, y};
        btn.change_button(state);
    }
    else if (logic_board.status() == Logic_board::FINISH)
    {
        btn.change_button(state);
        level.finished = true;
        block_buttons(true);
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
    if (blocked || btn->state() != Level::EMPTY) return;
    change_previous();

    Play_window* win = (Play_window*) own;
    Level::Cell_state state = win->option();
    int x = btn->x(), y = btn->y();
    Position pos {x, y};

    logic_board.set_click(pos, state);
    auto current = logic_board.current();
    auto empty = logic_board.get_empty();
    level.set_current(current, empty);
    win->update_current(level);

    change_digits(pos);

    if (logic_board.status() == Logic_board::OK)
        btn->change_button(state);

    else if (logic_board.status() == Logic_board::FINISH)
    {
        btn->change_button(state);
        level.finished = true;
        block_buttons(true);
        win->update_finished(level);
    }
    
    else if (logic_board.status() == Logic_board::MISTAKE)
    {
        mistake = {x, y};
        btn->change_button(logic_board.current()[x][y] == 4 ? Level::MISTAKE_CROSS : Level::MISTAKE_FILLED);
        level.hearts_count = level.hearts_count - 1;
        if (level.hearts_count == 0) block_buttons(true);
        win->update_heart_count(level);
    }
}