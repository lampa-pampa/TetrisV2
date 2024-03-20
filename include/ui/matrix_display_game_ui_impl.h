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

#include "action.h"
#include "brick.h"
#include "char.h"
#include "cube.h"
#include "iv_color.h"
#include "matrix_display.h"
#include "progress_bar.h"
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
        std::map<int, Action> key_code_to_action,
        uint_fast8_t ghost_color_value,
        uint_fast8_t border_color_id,
        uint_fast8_t font_color_id,
        uint_fast8_t empty_level_progress_bar_color_id,
        uint_fast8_t level_progress_bar_color_id);
    
    void handle_key_press(int key_code) override;
    void draw_level_progress_bar(int quantity) override;

    void draw_next_brick(const Brick& brick) override
    {
        this->draw_centered_brick_in_rectangle(brick, next_rectangle, false);
    }

    void draw_hold_brick(const Brick& brick) override
    {
        this->draw_centered_brick_in_rectangle(brick, hold_rectangle, true);
    }

    void draw_cur_brick(const std::vector<Cube>& cubes) override
    {
        this->cur_brick_cubes = cubes;
        this->draw_cubes(board_position, cubes);
    }

    void draw_ghost_brick(const std::vector<Cube>& cubes) override
    {
        this->draw_cubes(board_position, cubes, this->ghost_color_value);
    }

    void draw_board(const CubeMatrix& cubes) override
    {
        this->draw_board(board_position, cubes);
    }

    void draw_score(unsigned long long score) override
    {
        
    }
    
    void draw_level(int level) override
    {
        this->draw_on_text_area(this->get_number_as_string(
            level, level_value_digits_quantity), level_value_area);
    }

    void game_over() override
    {
        this->draw_on_text_area("GAME\nOVER", this->game_state_text_area);
        this->refresh();
    }

    void pause() override
    {
        this->draw_on_text_area("PAUSED", this->game_state_text_area);
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
    using IvColorMatrix = std::vector<std::vector<IvColor>>;
    using Signal = boost::signals2::signal<void()>;

    static constexpr int cube_size{3};
    static constexpr int level_value_digits_quantity{2};
    static constexpr Vector2 board_position{17, 2};
   
    static constexpr Rectangle next_rectangle{{48, 2}, 14, 8};
    static constexpr Rectangle hold_rectangle{{2, 2}, 14, 8};
    static constexpr Rectangle level_text_rectangle{{2, 12}, 13, 41};
    static constexpr Rectangle level_value_rectangle{{2, 55}, 13, 7};
   
    static constexpr ProgressBar level_progress_bar{{3, 13}, 11, 3, 10, 1};
   
    static constexpr TextArea game_state_text_area{ {{18, 3}, 28, 58} };
    static constexpr TextArea level_text_area{level_text_rectangle};
    static constexpr TextArea level_value_area{level_value_rectangle};

    const int display_width;
    const int display_height;
    const uint_fast8_t ghost_color_value;
    const uint_fast8_t border_color_id;
    const uint_fast8_t font_color_id;
    const uint_fast8_t empty_level_progress_bar_color_id;
    const uint_fast8_t level_progress_bar_color_id;
    const std::map<int, Action> key_code_to_action;
    const std::vector<Rectangle> background_rectangles
    {
        next_rectangle,
        hold_rectangle,
        level_text_rectangle,
        level_value_rectangle,
        {{49, 12}, 13, 50},
    };
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

    IvColorMatrix create_layer(IvColor color) const;
    Vector2 compute_brick_center(
        int width, int height, bool align_to_left) const;
    Vector2 compute_brick_centered_position(
        const Brick& brick, bool align_to_left) const;
    std::string get_number_as_string(int number, int width = 0) const;
    void draw_cube(
        Vector2 position, const Cube& cube, uint_fast8_t color_value);
    void draw_rectangle(const Rectangle& rectangle, IvColor color = {});
    void draw_text_line(const TextLine& line, IvColor color);
    void draw_centered_brick_in_rectangle(
        const Brick& brick, const Rectangle& rect, bool align_to_left);
    void emit_action_signal(Action action);

    void refresh() override
    {
        this->matrix.refresh(this->main_layer);
    }

    bool position_is_on_display(Vector2 position) const
    {
        return position.x >= 0 and position.x < display_width
            and position.y >= 0 and position.y < display_height;
    }

    void draw_on_text_area(std::string text, const TextArea& area)
    {
        this->draw_text_lines(area.create_lines(text), this->font_color_id);
    }

    void draw_text_lines(
        const std::vector<TextLine>& text_lines, IvColor color)
    { 
        for (const auto& line : text_lines)
            this->draw_text_line(line, color);
    }

    void draw_background()
    {
        this->draw_rectangles(this->background_rectangles);
    }

    void draw_rectangles(
        const std::vector<Rectangle>& rectangles, IvColor color = {})
    { 
        for (const auto& rectangle : rectangles)
            this->draw_rectangle(rectangle, color);
    }

    void draw_char(Vector2 position, Char c, IvColor color)
    {
        for (const auto& pixel_position : c.pixels)
            this->draw_pixel(position + pixel_position, color);
    }

    void draw_board(
        Vector2 position,
        const CubeMatrix& board,
        uint_fast8_t color_value = 0xff)
    {
        for (const auto& row : board)
            this->draw_cubes(position, row, color_value);
    }

    void draw_cubes(
        Vector2 position,
        const std::vector<Cube>& cubes,
        uint_fast8_t color_value = 0xff)
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