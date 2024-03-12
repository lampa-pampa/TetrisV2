#ifndef INCLUDE_MATRIX_DISPLAY_GAME_UI_IMPL_H
#define INCLUDE_MATRIX_DISPLAY_GAME_UI_IMPL_H

#include "game_ui.h"

#include <cassert>
#include <functional>
#include <map>
#include <vector>

#include <boost/signals2.hpp>
#include <ncurses.h>

#include "brick.h"
#include "color_name.h"
#include "cube.h"
#include "matrix_display.h"
#include "vector_2.h"

namespace Tetris
{

class MatrixDisplayGameUiImpl final: public GameUi
{
public:
    MatrixDisplayGameUiImpl(MatrixDisplay& matrix);
    
    void draw_new_centered_brick(
        Vector2 display_position, int display_width, int display_height,
        const Brick& brick);

    void draw_cur_brick(const std::vector<Cube>& cubes) override
    {
        this->cur_brick_cubes = cubes;
        this->draw_cubes(board_position, cubes);
    }

    void draw_ghost_brick(const std::vector<Cube>& cubes) override
    {
        this->ghost_brick_cubes = cubes;
        this->draw_transparent_cubes(board_position, cubes);
    }

    void draw_next_brick(const Brick& brick) override
    {
        this->next_brick_cubes = brick.cubes;
        this->draw_new_centered_brick(
            next_board_position, next_board_width, next_board_height, brick);
    }

    void draw_hold_brick(const Brick& brick) override
    {
        this->hold_brick_cubes = brick.cubes;
        this->draw_new_centered_brick(
            hold_board_position, next_board_width, next_board_height, brick);
    }

    void draw_board(const CubeMatrix& cubes) override
    {
        this->board_cubes = cubes;
        this->draw_board(board_position, cubes);
    }

    void input_received(int input) override
    {
        if (const auto it{this->input_to_signal.find(input)};
                it != this->input_to_signal.end())
            it->second();
    }

    void draw_score(unsigned long long score) override
    {

    }

    void draw_tetrises(unsigned long long tetrises) override
    {

    }

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

    void connect_move_left_pressed(
        const std::function<void()>& handler) override
    {
        this->move_left_pressed.connect(handler);
    }

    void connect_move_right_pressed(
        const std::function<void()>& handler) override
    {
        this->move_right_pressed.connect(handler);
    }

    void connect_rotate_clockwise_pressed(
        const std::function<void()>& handler) override
    {
        this->rotate_clockwise_pressed.connect(handler);
    }

    void connect_rotate_counter_clockwise_pressed(
        const std::function<void()>& handler) override
    {
        this->rotate_counter_clockwise_pressed.connect(handler);
    }

    void connect_soft_drop_pressed(
        const std::function<void()>& handler) override
    {
        this->soft_drop_pressed.connect(handler);
    }

    void connect_hard_drop_pressed(
        const std::function<void()>& handler) override
    {
        this->hard_drop_pressed.connect(handler);
    }

    void connect_hold_pressed(
        const std::function<void()>& handler) override
    {
        this->hold_pressed.connect(handler);
    }

    void connect_pause_pressed(
        const std::function<void()>& handler) override
    {
        this->handle_pause_pressed.connect(handler);
    }

private:
    using ColorCodeMatrix = std::vector<std::vector<int>>;
    using Signal = boost::signals2::signal<void()>;

    static constexpr int cube_size{3};
    static constexpr ColorName background_color{ColorName::white};
    static constexpr Vector2 board_position{17, -4};
    static constexpr int next_board_width{14};
    static constexpr int next_board_height{8};
    static constexpr Vector2 next_board_position{48, 2};
    static constexpr Vector2 hold_board_position{2, 2};

    const int display_width;
    const int display_height;
    const std::map<int, Signal&> input_to_signal
    {
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
    std::vector<Cube> cur_brick_cubes;
    std::vector<Cube> ghost_brick_cubes;
    std::vector<Cube> next_brick_cubes;
    std::vector<Cube> hold_brick_cubes;

    Signal move_left_pressed;
    Signal move_right_pressed;
    Signal rotate_clockwise_pressed;
    Signal rotate_counter_clockwise_pressed;
    Signal soft_drop_pressed;
    Signal hard_drop_pressed;
    Signal hold_pressed;
    Signal handle_pause_pressed;

    ColorCodeMatrix create_color_codes() const;
    Vector2 compute_brick_center(const Brick& brick) const;
    Vector2 compute_brick_on_display_centered_position(
        Vector2 display_position, int display_width, int display_height,
        const Brick& brick) const;
    void draw_rectangle(
        Vector2 position, int width, int height,
        int color_code = Cube::black_color_code);

    void refresh() override
    {
        this->matrix.refresh(this->color_codes);
    }

    Vector2 compute_display_center(int display_width, int display_height) const
    {
        return Vector2{display_width, display_height} / 2;
    }

    bool position_is_on_display(Vector2 position) const
    {
        return position.x >= 0 and position.x < display_width
            and position.y >= 0 and position.y < display_height;
    }

    void draw_background()
    {
        this->draw_rectangle(
            {0, 0}, display_width, display_height,
            create_color(background_color));
    }

    void draw_board(Vector2 position, const CubeMatrix& board)
    {
        for (const auto& row : board)
            this->draw_cubes(position, row);
    }

    void draw_cubes(Vector2 position, const std::vector<Cube>& cubes)
    {
        for (const auto& cube : cubes)
            this->draw_cube(position, cube);
    }

    void draw_transparent_cubes(
        Vector2 position, const std::vector<Cube>& cubes)
    {
        for (const auto& cube : cubes)
            this->draw_transparent_cube(position, cube);
    }

    void draw_cube(Vector2 position, const Cube& cube)
    {
        const Vector2 position_in_px{position + cube.position * cube_size};
        this->draw_rectangle(
            position_in_px, cube_size, cube_size, cube.color_code);
    }

    void draw_transparent_cube(Vector2 position, const Cube& cube)
    {
        const Vector2 position_in_px{position + cube.position * cube_size};
        this->draw_pixel(position_in_px + cube_size / 2, cube.color_code);
    }

    void draw_pixel(Vector2 position, int color_code)
    {
        assert(this->position_is_on_display(position));
        this->color_codes[position.y][position.x] = color_code;
    }
};

}

#endif