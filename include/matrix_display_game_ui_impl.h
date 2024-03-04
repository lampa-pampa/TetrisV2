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
#include "cube.h"
#include "vector_2.h"

namespace Tetris
{

class MatrixDisplayGameUiImpl final: public GameUi
{
    using ColorCodeMatrix = std::vector<std::vector<int>>;
    using CubeMatrix = std::vector<std::vector<Cube>>;
    using Signal = boost::signals2::signal<void()>;

    static constexpr int cube_size{3};
    static constexpr int border_width{2};
    static constexpr int center_x{30 + border_width};
    static constexpr int max_brick_height{3};
    static constexpr int max_brick_width{4};
    static constexpr ColorName border_color{ColorName::white};
    static constexpr Vector2 board_position{border_width, border_width};
    static constexpr Vector2 next_brick_position{46, border_width + 2 * cube_size};
    static constexpr Vector2 hold_brick_position{
        46, 2 * border_width + cube_size * (max_brick_height + 3)
    };

    const std::map<int, Signal&> input_to_signal{
        {KEY_LEFT, this->move_left_pressed},
        {KEY_RIGHT, this->move_right_pressed},
        {KEY_UP, this->rotate_clockwise_pressed},
        {KEY_DOWN, this->soft_drop_pressed},
        {' ', this->hard_drop_pressed},
        {'c', this->hold_pressed},
        {'z', this->rotate_counter_clockwise_pressed},
        {'p', this->handle_pause_pressed},
    };
    
    MatrixDisplay& matrix;
    ColorCodeMatrix color_codes;
    CubeMatrix board_cubes;
    Brick next_brick;
    Brick hold_brick;

    Signal move_left_pressed;
    Signal move_right_pressed;
    Signal rotate_clockwise_pressed;
    Signal rotate_counter_clockwise_pressed;
    Signal soft_drop_pressed;
    Signal hard_drop_pressed;
    Signal hold_pressed;
    Signal handle_pause_pressed;

    void draw_border();
    void draw_rectangle(Vector2 position, int width, int height, ColorName color);
    void draw_cube(Vector2 position, int color_code);
    void draw_board(Vector2 position, const CubeMatrix& board);
    void draw_brick(Vector2 position, std::vector<Cube> cubes);
    void cover_brick_with_rectangle(Vector2 position);

    bool position_is_on_display(Vector2 position) const
    {
        return position.x >= 0 and position.x < this->matrix.get_width()
            and position.y >= 0 and position.y < this->matrix.get_height();
    }

    void draw_pixel(Vector2 position, int color_code)
    {
        assert(this->position_is_on_display(position));
        this->color_codes[position.y][position.x] = color_code;
    }

public:
    MatrixDisplayGameUiImpl(MatrixDisplay& matrix);
    
    void draw_board(const CubeMatrix& cubes) override;
    void draw_score(unsigned long long score) override;
    void draw_next(const Brick& brick) override;
    void draw_hold(const Brick& brick) override;
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
        this->draw_board(this->board_cubes);
    }

    void connect_move_left_pressed(const std::function<void()>& handler) override
    {
        this->move_left_pressed.connect(handler);
    }

    void connect_move_right_pressed(const std::function<void()>& handler) override
    {
        this->move_right_pressed.connect(handler);
    }

    void connect_rotate_clockwise_pressed(const std::function<void()>& handler) override
    {
        this->rotate_clockwise_pressed.connect(handler);
    }

    void connect_rotate_counter_clockwise_pressed(
        const std::function<void()>& handler
    ) override {
        this->rotate_counter_clockwise_pressed.connect(handler);
    }

    void connect_soft_drop_pressed(const std::function<void()>& handler) override
    {
        this->soft_drop_pressed.connect(handler);
    }

    void connect_hard_drop_pressed(const std::function<void()>& handler) override
    {
        this->hard_drop_pressed.connect(handler);
    }

    void connect_hold_pressed(const std::function<void()>& handler) override
    {
        this->hold_pressed.connect(handler);
    }

    void connect_pause_pressed(const std::function<void()>& handler) override
    {
        this->handle_pause_pressed.connect(handler);
    }
};

}

#endif