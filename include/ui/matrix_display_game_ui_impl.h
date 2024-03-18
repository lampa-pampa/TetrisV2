#ifndef INCLUDE_UI_MATRIX_DISPLAY_GAME_UI_IMPL_H
#define INCLUDE_UI_MATRIX_DISPLAY_GAME_UI_IMPL_H

#include "game_ui.h"

#include <cassert>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include <boost/signals2.hpp>

#include "action.h"
#include "brick.h"
#include "cube.h"
#include "matrix_display.h"
#include "char.h"
#include "text_area.h"
#include "rectangle.h"
#include "vector_2.h"

namespace Tetris::Ui
{

class MatrixDisplayGameUiImpl final: public GameUi
{
public:
    MatrixDisplayGameUiImpl(
        MatrixDisplay& matrix,
        std::map<int, Action> key_code_to_action,
        int background_color_code,
        int border_color_code,
        int font_color_code);
    
    void handle_key_press(int key_code) override;
    void draw_next_brick(const Brick& brick) override
    {

    }

    void draw_hold_brick(const Brick& brick) override
    {

    }

    void draw_cur_brick(const std::vector<Cube>& cubes) override
    {
        this->cur_brick_cubes = cubes;
        this->draw_cubes(board_position, cubes);
    }

    void draw_ghost_brick(const std::vector<Cube>& cubes) override
    {
        this->draw_transparent_cubes(board_position, cubes);
    }

    void draw_board(const CubeMatrix& cubes) override
    {
        this->draw_board(board_position, cubes);
    }

    void draw_score(unsigned long long score) override
    {
        
    }

    void draw_lines_quantity(int quantity) override
    {
        
    }
    
    void draw_level(int level) override
    {

    }

    void game_over() override
    {
        this->draw_on_text_area("GAME\nOVER", this->game_state_text_area);
    }

    void pause() override
    {
        this->draw_on_text_area("LEVEL\nPAUSED", this->game_state_text_area);
        this->refresh();
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
    using ColorCodeMatrix = std::vector<std::vector<int>>;
    using Signal = boost::signals2::signal<void()>;

    const int display_width;
    const int display_height;
    const int background_color_code;
    const int border_color_code;
    const int font_color_code;
    const std::map<int, Action> key_code_to_action;
    const std::map<Action, Signal&> action_to_signal
    {
        {Action::move_left, this->move_left_pressed},
        {Action::move_right, this->move_right_pressed},
        {Action::rotate_clockwise, this->rotate_clockwise_pressed},
        {Action::soft_drop, this->soft_drop_pressed},
        {Action::locking_hard_drop, this->locking_hard_drop_pressed},
        {Action::no_locking_hard_drop, this->no_locking_hard_drop_pressed},
        {Action::rotate_counter_clockwise,
            this->rotate_counter_clockwise_pressed},
        {Action::hold, this->hold_pressed},
    };

    static constexpr int cube_size{3};
    static constexpr Vector2 board_position{17, -4};
    static constexpr Rectangle next_rectangle{{48, 2}, 14, 8};
    static constexpr Rectangle hold_rectangle{{2, 2}, 14, 8};
    const inline static std::vector background_rectangles{
        next_rectangle,
        hold_rectangle,
        {{2, 12}, 13, 50},
        {{49, 12}, 13, 50},
    };
    const TextArea game_state_text_area{
        {17, 2}, 30, 60, this->font_color_code, true, Align::center, Align::center
    };
    const TextArea level_text_area{{2, 12}, 0, 0, this->font_color_code};
    
    MatrixDisplay& matrix;
    ColorCodeMatrix color_codes;
    std::vector<Cube> cur_brick_cubes;
    
    Signal move_left_pressed;
    Signal move_right_pressed;
    Signal rotate_clockwise_pressed;
    Signal rotate_counter_clockwise_pressed;
    Signal soft_drop_pressed;
    Signal locking_hard_drop_pressed;
    Signal no_locking_hard_drop_pressed;
    Signal hold_pressed;

    ColorCodeMatrix create_color_codes() const;
    Vector2 compute_brick_center(
        int width, int height, bool align_to_left) const;
    Vector2 compute_brick_centered_position(
        const Brick& brick, bool align_to_left) const;
    void draw_background();
    void draw_cube(Vector2 position, const Cube& cube);
    void draw_rectangle(const Rectangle& rectangle);
    void emit_action_signal(Action action);

    void refresh() override
    {
        this->matrix.refresh(this->color_codes);
    }

    bool position_is_on_display(Vector2 position) const
    {
        return position.x >= 0 and position.x < display_width
            and position.y >= 0 and position.y < display_height;
    }

    void draw_on_text_area(std::string text, const TextArea& area)
    {
        this->draw_text_lines(area.create_lines(text));
    }

    void draw_text_lines(const std::vector<TextLine>& text_lines)
    { 
        for(const auto& line : text_lines)
            this->draw_text_line(line);
    }

    void draw_text_line(const TextLine& line)
    {
        this->draw_rectangle(line.background);
        Vector2 position{line.position};
        for(const auto& chr : line.chars)
        {
            this->draw_char(position, chr, line.color_code);
            position.x += chr.width + Char::separator;
        }
    }

    void draw_char(Vector2 position, Char c, int color_code)
    {
        for(const auto& pixel_position : c.pixels)
            this->draw_pixel(position + pixel_position, color_code);
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