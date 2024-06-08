#ifndef INCLUDE_UI_MATRIX_DISPLAY_GAME_UI_IMPL_H
#define INCLUDE_UI_MATRIX_DISPLAY_GAME_UI_IMPL_H

#include "brick/brick.h"
#include "ui/color/iv_color.h"
#include "ui/game_ui/game_ui.h"

#include <cassert>
#include <deque>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include <boost/range/irange.hpp>
#include <boost/signals2/signal.hpp>

#include "ui/game_ui/config.h"
#include "ui/matrix_display/matrix_display.h"
#include "ui/render/sprite.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class MatrixDisplayGameUiImpl final: public GameUi
{
public:
    using IvColorMatrix = std::vector<std::vector<IvColor>>;
    using Signal = boost::signals2::signal<void()>;

    MatrixDisplayGameUiImpl(MatrixDisplay& matrix, const GameUiConfig& config);

    void refresh_background() override;

    void refresh_level_progress_bar(int count) override
    {
        draw_sprites(config_.graphic_engine.level.progress_bar.render(count));
        draw_sprites(config_.graphic_engine.level.display.label.display.render(
            config_.graphic_engine.level.display.label.text));
    }

    void pause() override
    {
        draw_sprites(config_.graphic_engine.main.display.render(
            config_.state_messages.paused));
    }

    void game_over() override
    {
        draw_sprites(config_.graphic_engine.main.display.render(
            config_.state_messages.game_over));
    }

    void refresh_score(unsigned long long score) override
    {
        draw_sprites(config_.graphic_engine.score.value.display.render(
            score, config_.graphic_engine.score.value.max_length));
    }

    void refresh_next_bricks(const std::deque<Brick>& bricks) override
    {
        draw_sprites(config_.graphic_engine.next.render(bricks));
    }

    void refresh_hold_brick(const Brick& brick) override
    {
        draw_sprites(config_.graphic_engine.hold.render(brick));
    }

    void refresh_level(int level) override
    {
        draw_sprites(config_.graphic_engine.level.display.value.display.render(
            level, config_.graphic_engine.level.display.value.max_length));
    }

    void refresh_cur_brick(const std::vector<Cube>& cubes) override
    {
        draw_sprites(config_.graphic_engine.board.display.render(cubes));
    }

    void refresh_ghost_brick(const std::vector<Cube>& cubes) override
    {
        draw_sprites(config_.graphic_engine.board.display.render(
            cubes, config_.graphic_engine.board.ghost_color_value));
    }

    void refresh_board(const CubeMatrix& cubes) override
    {
        for (const auto& row : cubes)
            draw_sprites(config_.graphic_engine.board.display.render(row));
    }

    void handle_key_press(int key_code) override
    {
        if (const auto it{key_code_to_signal_.find(key_code)};
            it != key_code_to_signal_.end())
            it->second();
    }

    void flush_matrix() override
    {
        matrix_display_.refresh(main_layer_);
    }

    void connect_move_left_pressed(
        const std::function<void()>& handler) override
    {
        move_left_pressed_.connect(handler);
    }

    void connect_move_right_pressed(
        const std::function<void()>& handler) override
    {
        move_right_pressed_.connect(handler);
    }

    void connect_rotate_clockwise_pressed(
        const std::function<void()>& handler) override
    {
        rotate_clockwise_pressed_.connect(handler);
    }

    void connect_rotate_counter_clockwise_pressed(
        const std::function<void()>& handler) override
    {
        rotate_counter_clockwise_pressed_.connect(handler);
    }

    void connect_soft_drop_pressed(
        const std::function<void()>& handler) override
    {
        soft_drop_pressed_.connect(handler);
    }

    void connect_locking_hard_drop_pressed(
        const std::function<void()>& handler) override
    {
        locking_hard_drop_pressed_.connect(handler);
    }

    void connect_no_locking_hard_drop_pressed(
        const std::function<void()>& handler) override
    {
        no_locking_hard_drop_pressed_.connect(handler);
    }

    void connect_hold_pressed(const std::function<void()>& handler) override
    {
        hold_pressed_.connect(handler);
    }

private:
    MatrixDisplay& matrix_display_;
    const GameUiConfig& config_;
    const std::map<int, Signal&> key_code_to_signal_;
    IvColorMatrix main_layer_;

    Signal move_left_pressed_;
    Signal move_right_pressed_;
    Signal rotate_clockwise_pressed_;
    Signal rotate_counter_clockwise_pressed_;
    Signal soft_drop_pressed_;
    Signal locking_hard_drop_pressed_;
    Signal no_locking_hard_drop_pressed_;
    Signal hold_pressed_;

    IvColorMatrix create_layer(const Vector2& size) const
    {
        return IvColorMatrix(size.y, std::vector<IvColor>(size.x));
    }

    void draw_sprites(const Sprites& sprites)
    {
        for (const auto& sprite : sprites)
            draw_sprite(sprite, main_layer_);
    }

    void draw_sprites(const Sprites& sprites, IvColorMatrix& layer)
    {
        for (const auto& sprite : sprites)
            draw_sprite(sprite, layer);
    }

    void draw_sprite(const Sprite& sprite)
    {
        draw_sprite(sprite, main_layer_);
    }

    void draw_sprite(const Sprite& sprite, IvColorMatrix& layer)
    {
        for (const auto& pixel : sprite.pixels)
            draw_pixel(sprite.position + pixel, sprite.color, layer);
    }

    void draw_pixel(
        const Vector2& position, const IvColor& color, IvColorMatrix& layer)
    {
        if (position >= 0 and position < matrix_display_.get_size())
            layer[position.y][position.x] = color;
    }
};

} // namespace Tetris::Ui

#endif
