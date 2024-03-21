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
        this->draw_centered_brick_in_container(brick, next_container, false);
    }

    void draw_hold_brick(const Brick& brick) override
    {
        this->draw_centered_brick_in_container(brick, hold_container, true);
    }

    void draw_cur_brick(const std::vector<Cube>& cubes) override
    {
        this->cur_brick_cubes = cubes;
        this->draw_cubes(board_container.position, cubes);
    }

    void draw_ghost_brick(const std::vector<Cube>& cubes) override
    {
        this->draw_cubes(
            board_container.position, cubes, this->ghost_color_value);
    }

    void draw_board(const CubeMatrix& cubes) override
    {
        this->draw_board(board_container.position, cubes);
    }

    void draw_score(unsigned long long score) override
    {
        this->draw_on_text_area(this->get_number_as_string(
            score, score_value_digits_quantity), score_value_area);
    }

    void draw_tetrises(unsigned long long tetrises) override
    {
        this->draw_on_text_area(this->get_number_as_string(
            tetrises, tetrises_value_digits_quantity), tetrises_value_area);
    }
    
    void draw_level(int level) override
    {
        this->draw_on_text_area(this->get_number_as_string(
            level, level_value_digits_quantity), level_value_area);
    }

    void game_over() override
    {
        this->draw_on_text_area(
            this->game_over_text, this->game_state_text_area);
        this->refresh();
    }

    void pause() override
    {
        this->draw_on_text_area(this->paused_text, this->game_state_text_area);
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
    static constexpr int level_value_digits_quantity{3};
    static constexpr int score_value_digits_quantity{9};
    static constexpr int tetrises_value_digits_quantity{6};

    const std::string level_text{"L\nE\nV\nE\nL"};
    const std::string paused_text{"PAUSED"};
    const std::string game_over_text{"GAME\nOVER"};
    const std::string score_text{"PTS"};
    const std::string tetrises_text{"TET"};
   
    static constexpr Rectangle board_container{{17, 2}, {30, 60}};
    static constexpr Rectangle hold_container{{2, 2}, {14, 8}};
    static constexpr Rectangle next_container{{48, 2}, {14, 8}};
    static constexpr Rectangle level_text_container{{2, 12}, {13, 41}};
    static constexpr Rectangle level_value_container{{2, 55}, {13, 7}};
    static constexpr Rectangle score_text_container{{49, 12}, {13, 7}};
    static constexpr Rectangle score_value_container{{49, 20}, {13, 19}};
    static constexpr Rectangle tetrises_text_container{{49, 41}, {13, 7}};
    static constexpr Rectangle tetrises_value_container{{49, 49}, {13, 13}};
   
    static constexpr ProgressBar level_progress_bar{{3, 13}, {11, 3}, 10, 1};
   
    static constexpr TextArea game_state_text_area{board_container};
    static constexpr TextArea level_text_area{level_text_container};
    static constexpr TextArea level_value_area{level_value_container};
    static constexpr TextArea score_text_area{score_text_container};
    static constexpr TextArea score_value_area{score_value_container};
    static constexpr TextArea tetrises_text_area{tetrises_text_container};
    static constexpr TextArea tetrises_value_area{tetrises_value_container};

    const uint_fast8_t ghost_color_value;
    const uint_fast8_t border_color_id;
    const uint_fast8_t font_color_id;
    const uint_fast8_t empty_level_progress_bar_color_id;
    const uint_fast8_t level_progress_bar_color_id;
    const std::map<int, Action> key_code_to_action;
    const std::vector<Rectangle> containers
    {
        next_container,
        hold_container,
        level_text_container,
        level_value_container,
        board_container,
        score_text_container,
        score_value_container,
        tetrises_text_container,
        tetrises_value_container,
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

    IvColorMatrix create_layer(Vector2 size, IvColor color) const;
    Vector2 compute_brick_center(
        Vector2 brick_position, bool align_to_left) const;
    Vector2 compute_brick_centered_position(
        const Brick& brick, bool align_to_left) const;
    std::string get_number_as_string(int number, int width = 0) const;
    void draw_background();
    void draw_cube(
        Vector2 position, const Cube& cube, uint_fast8_t color_value);
    void draw_rectangle(const Rectangle& rectangle, IvColor color = {});
    void draw_text_line(const TextLine& line, IvColor color);
    void draw_centered_brick_in_container(
        const Brick& brick, const Rectangle& rect, bool align_to_left);
    void emit_action_signal(Action action);

    void refresh() override
    {
        this->matrix.refresh(this->main_layer);
    }

    bool position_is_on_display(Vector2 position) const
    {
        return position >= 0 and position < this->matrix.get_size();
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