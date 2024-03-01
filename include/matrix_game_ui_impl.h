#ifndef INCLUDE_MATRIX_GAME_UI_IMPL_H
#define INCLUDE_MATRIX_GAME_UI_IMPL_H

#include <functional>
#include <map>
#include <vector>

#include <boost/signals2.hpp>
#include <ncurses.h>

#include "brick.h"
#include "color.h"
#include "game_ui.h"
#include "ncurses_colors.h"
#include "pixel.h"
#include "vector_2.h"

namespace Tetris
{

class MatrixGameUiImpl final: public GameUi
{
    using Pixels = std::vector<std::vector<Pixel>>;
    using Signal = boost::signals2::signal<void()>;

    static constexpr int dot_width_chr{2};
    static constexpr int dot_height_chr{1};
    static constexpr int display_width_dot{64};
    static constexpr int display_height_dot{64};
    static constexpr int pixel_size_dot{3};
    static constexpr int border_width_dot{2};
    static constexpr int game_board_width_px{10};
    static constexpr Vector2 board_position_dot{
        border_width_dot,
        border_width_dot
    };
    static constexpr Color border_color{Color::white};
    static constexpr wchar_t dot_char{L'◼'};

    static constexpr int display_width_chr{
        display_width_dot * dot_width_chr
    };
    static constexpr int display_height_chr{
        display_height_dot * dot_height_chr
    };
    static constexpr int max_x_dot{display_width_dot - 1};
    static constexpr int max_y_dot{display_height_dot - 1};
    static constexpr int max_border_width_dot{border_width_dot - 1};
    static constexpr int game_board_width_dot{
        pixel_size_dot * game_board_width_px
    };
    static constexpr int center_x_dot{
        game_board_width_dot + border_width_dot
    };
    
    const std::map<int, Signal&> input_to_signal{
        {KEY_LEFT, this->move_left_pressed},
        {KEY_RIGHT, this->move_right_pressed},
        {KEY_UP, this->rotate_pressed},
        {KEY_DOWN, this->soft_drop_pressed},
        {' ', this->hard_drop_pressed},
        {'c', this->hold_pressed},
        {'p', this->handle_pause_pressed},
    };
    int width;
    int height;
    Pixels game_board_pixels{};
    NCursesColors ncurses_colors;
    ::WINDOW* window;
    Signal move_left_pressed;
    Signal move_right_pressed;
    Signal rotate_pressed;
    Signal soft_drop_pressed;
    Signal hard_drop_pressed;
    Signal hold_pressed;
    Signal handle_pause_pressed;

    void create_window();
    void set_pixel(int x, int y, Color color);
    void draw_border();
    void draw_line(Vector2 from, Vector2 to, Color color);
    void print_board(const Pixels& pixels, Vector2 position);
    void print_pixel(int d_start_x, int d_start_y, Color color);

public:
    MatrixGameUiImpl(const NCursesColors& ncurses_colors);
    
    ~MatrixGameUiImpl()
    {
        ::endwin();
    }

    void draw_board(const Pixels& pixels) override;
    void draw_next(const Brick& brick) override;
    void draw_hold(const Brick& brick) override;
    void draw_score(unsigned long long score) override;
    void draw_tetrises(unsigned long long tetrises) override;
    void input_received(int input);

    WINDOW * get_game_window()
    {
        return this->window;
    }

    void game_over() override
    {
        
    }

    void pause() override
    {
        
    }

    void resume() override
    {
        this->draw_board(this->game_board_pixels);
    }

    void connect_move_left_pressed(std::function<void()> handler) override
    {
        this->move_left_pressed.connect(handler);
    }

    void connect_move_right_pressed(std::function<void()> handler) override
    {
        this->move_right_pressed.connect(handler);
    }

    void connect_rotate_pressed(std::function<void()> handler) override
    {
        this->rotate_pressed.connect(handler);
    }

    void connect_soft_drop_pressed(std::function<void()> handler) override
    {
        this->soft_drop_pressed.connect(handler);
    }

    void connect_hard_drop_pressed(std::function<void()> handler) override
    {
        this->hard_drop_pressed.connect(handler);
    }

    void connect_hold_pressed(std::function<void()> handler) override
    {
        this->hold_pressed.connect(handler);
    }

    void connect_pause_pressed(std::function<void()> handler) override
    {
        this->handle_pause_pressed.connect(handler);
    }
};

}

#endif