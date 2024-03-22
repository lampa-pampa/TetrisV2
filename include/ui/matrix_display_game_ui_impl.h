#ifndef INCLUDE_UI_MATRIX_DISPLAY_GAME_UI_IMPL_H
#define INCLUDE_UI_MATRIX_DISPLAY_GAME_UI_IMPL_H

#include "game_ui.h"

#include <cassert>
#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include <boost/signals2.hpp>

#include "brick.h"
#include "char.h"
#include "cube.h"
#include "game_ui_colors.h"
#include "game_ui_components.h"
#include "game_ui_controls.h"
#include "iv_color.h"
#include "matrix_display.h"
#include "rectangle.h"
#include "text_area.h"
#include "vector_2.h"

namespace Tetris::Ui
{

class MatrixDisplayGameUiImpl final: public GameUi
{
public:
    MatrixDisplayGameUiImpl(
        MatrixDisplay& matrix,
        GameUiControls controls,
        GameUiComponents components,
        GameUiColors colors,
        int cube_size);
    
    void handle_key_press(int key_code) override;
    void refresh_level_progress_bar(int quantity) override;
    void pause() override;
    void game_over() override;
    void refresh_next_brick(const Brick& brick) override;
    void refresh_hold_brick(const Brick& brick) override;
    void refresh_score(unsigned long long score) override;
    void refresh_tetrises(unsigned long long tetrises) override;
    void refresh_level(int level) override;
    
    void refresh_cur_brick(const std::vector<Cube>& cubes) override
    {
        this->cur_brick_cubes = cubes;
        this->draw_on_board(cubes, this->colors.value.brick.cur);
    }

    void refresh_ghost_brick(const std::vector<Cube>& cubes) override
    {
        this->draw_on_board(cubes, this->colors.value.brick.ghost);
    }

    void refresh_board(const CubeMatrix& cubes) override
    {
        this->draw_on_board(cubes);
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

    void connect_locking_hard_drop_pressed(
        const std::function<void()>& handler) override
    {
        this->locking_hard_drop_pressed.connect(handler);
    }

    void connect_no_locking_hard_drop_pressed(
        const std::function<void()>& handler) override
    {
        this->no_locking_hard_drop_pressed.connect(handler);
    }

    void connect_hold_pressed(
        const std::function<void()>& handler) override
    {
        this->hold_pressed.connect(handler);
    }

private:
    using IvColorMatrix = std::vector<std::vector<IvColor>>;
    using Signal = boost::signals2::signal<void()>;

    const std::map<int, Signal&> key_code_to_signal;
    const GameUiComponents components;
    const GameUiColors colors;
    const int cube_size;

    MatrixDisplay& matrix;
    IvColorMatrix main_layer;
    std::vector<Cube> cur_brick_cubes;
    
    Signal move_left_pressed;
    Signal move_right_pressed;
    Signal rotate_clockwise_pressed;
    Signal rotate_counter_clockwise_pressed;
    Signal soft_drop_pressed;
    Signal locking_hard_drop_pressed;
    Signal no_locking_hard_drop_pressed;
    Signal hold_pressed;

    IvColorMatrix create_layer(Vector2 size, IvColor color) const;
    Vector2 compute_brick_center(
        Vector2 brick_position, bool align_to_left) const;
    Vector2 compute_brick_centered_position(
        const Brick& brick, bool align_to_left) const;
    void draw_background();
    void draw_cube(
        Vector2 position, const Cube& cube, uint_fast8_t color_value);
    void draw_rectangle(const Rectangle& rectangle, IvColor color);
    void draw_rectangle(const Rectangle& rectangle);
    void draw_text_line(const TextLine& line, IvColor color);
    void draw_centered_brick_in_container(
        const Brick& brick,
        const Rectangle& rect,
        uint_fast8_t color_value,
        bool align_to_left);

    void flush_matrix() override
    {
        this->matrix.refresh(this->main_layer);
    }

    bool position_is_on_display(Vector2 position) const
    {
        return position >= 0 and position < this->matrix.get_size();
    }

    void draw_on_text_area(
        std::string text, const TextArea& area, IvColor color)
    {
        this->draw_text_lines(area.create_lines(text), color);
    }

    void draw_on_text_area(
        unsigned long long number, const TextArea& area, IvColor color)
    {
        this->draw_on_text_area(std::to_string(number), area, color);
    }

    void draw_text_lines(
        const std::vector<TextLine>& text_lines, IvColor color)
    { 
        for (const auto& line : text_lines)
            this->draw_text_line(line, color);
    }

    void draw_rectangles(const std::vector<Rectangle>& rectangles)
    { 
        for (const auto& rectangle : rectangles)
            this->draw_rectangle(rectangle);
    }

    void draw_rectangles(
        const std::vector<Rectangle>& rectangles, IvColor color)
    { 
        for (const auto& rectangle : rectangles)
            this->draw_rectangle(rectangle, color);
    }

    void draw_char(Vector2 position, Char c, IvColor color)
    {
        for (const auto& pixel_position : c.pixels)
            this->draw_pixel(position + pixel_position, color);
    }

    void draw_on_board(const CubeMatrix& board)
    {
        for (const auto& row : board)
            this->draw_on_board(row, this->colors.value.board);
    }

    void draw_on_board(
        const std::vector<Cube>& cubes, uint_fast8_t color_value)
    {
        this->draw_cubes(
            this->components.container.board.position, cubes, color_value);
    }

    void draw_cubes(
        Vector2 position,
        const std::vector<Cube>& cubes,
        uint_fast8_t color_value)
    {
        for (const auto& cube : cubes)
            this->draw_cube(position, cube, color_value);
    }

    void draw_pixel(Vector2 position, IvColor color)
    {
        assert(this->position_is_on_display(position));
        this->main_layer[position.y][position.x] = color;
    }
};

}

#endif