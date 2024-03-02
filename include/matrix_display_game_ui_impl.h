#ifndef INCLUDE_MATRIX_DISPLAY_GAME_UI_IMPL_H
#define INCLUDE_MATRIX_DISPLAY_GAME_UI_IMPL_H

#include <cassert>
#include <functional>
#include <map>
#include <vector>

#include <boost/signals2.hpp>
#include <ncurses.h>

#include "brick.h"
#include "color_name.h"
#include "game_ui.h"
#include "matrix.h"
#include "pixel.h"
#include "vector_2.h"

namespace Tetris
{

class MatrixDisplayGameUiImpl final: public GameUi
{
    using ColorCodes = std::vector<std::vector<int>>;
    using Pixels = std::vector<std::vector<Pixel>>;
    using Signal = boost::signals2::signal<void()>;

    static constexpr int pixel_size{3};
    static constexpr int border_width{2};
    static constexpr int game_board_width{10};
    static constexpr Vector2 game_board_position{
        border_width,
        border_width
    };
    static constexpr ColorName border_color{ColorName::white};
    
    const std::map<int, Signal&> input_to_signal{
        {KEY_LEFT, this->move_left_pressed},
        {KEY_RIGHT, this->move_right_pressed},
        {KEY_UP, this->rotate_pressed},
        {KEY_DOWN, this->soft_drop_pressed},
        {' ', this->hard_drop_pressed},
        {'c', this->hold_pressed},
        {'p', this->handle_pause_pressed},
    };
    
    MatrixDisplay& matrix;
    ColorCodes color_codes;
    Pixels game_board_pixels;
    Signal move_left_pressed;
    Signal move_right_pressed;
    Signal rotate_pressed;
    Signal soft_drop_pressed;
    Signal hard_drop_pressed;
    Signal hold_pressed;
    Signal handle_pause_pressed;

    ColorCodes create_color_codes(int width, int height);
    void draw_border();
    void draw_rectangle(
        Vector2 position,
        int width,
        int height,
        ColorName color
    );
    void draw_board_pixel(Vector2 position, int color_code);
    void draw_board(Vector2 position, const Pixels& board);

    void draw_pixel(int x, int y, int color_code)
    {
        assert(this->position_is_on_display({x, y}));
        this->color_codes[y][x] = color_code;
    }

    bool position_is_on_display(Vector2 position) const
    {
        return position.x >= 0 and position.x < this->matrix.get_width()
            and position.y >= 0 and position.y < this->matrix.get_height();
    }


public:
    MatrixDisplayGameUiImpl(MatrixDisplay& matrix);
    
    void draw_game_board(const Pixels& pixels) override;
    void draw_next(const Brick& brick) override;
    void draw_hold(const Brick& brick) override;
    void draw_score(unsigned long long score) override;
    void draw_tetrises(unsigned long long tetrises) override;
    void input_received(int input);

    void game_over() override
    {
        
    }

    void pause() override
    {
        
    }

    void resume() override
    {
        this->draw_game_board(this->game_board_pixels);
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