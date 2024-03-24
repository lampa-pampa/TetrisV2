#ifndef INCLUDE_GAME_IMPL_H
#define INCLUDE_GAME_IMPL_H

#include "game.h"

#include <functional>
#include <vector>

#include <boost/signals2.hpp>

#include "board.h"
#include "brick_generator.h"
#include "brick.h"
#include "score_counter.h"
#include "settings.h"
#include "ui/game_ui.h"
#include "vector_2.h"

namespace Tetris
{

class GameImpl final: public Game
{
public:
    GameImpl(
        Ui::GameUi& ui,
        Board& board,
        BrickGenerator& brick_generator,
        ScoreCounter& score_counter,
        const Settings& settings,
        Vector2 brick_start_position,
        int next_level_lines_quantity);

    GameImpl(const GameImpl&) = delete;
    GameImpl(const GameImpl&&) = delete;

    Brick get_transformed_cur_brick() const;
    void resume() override;

    void pause() override
    {
        ui_.pause();
        state_ = GameState::paused;
    }

    void game_over() override
    {
        ui_.game_over();
    }

    GameState get_state() const override
    {
        return state_;
    }

    void handle_soft_drop() override
    {
        perform_action([this](){ soft_drop(); });
    }

    void handle_timeout() override
    {
        perform_action([this](){ tick(); });
    }

    void handle_move_left() override
    {
        perform_action([this](){ move_left(); });
    }

    void handle_move_right() override
    {
        perform_action([this](){ move_right(); });
    }

    void handle_rotate_clockwise() override
    {
        perform_action([this](){ rotate_clockwise(); });
    }

    void handle_rotate_counter_clockwise() override
    {
        perform_action([this](){rotate_counter_clockwise();});
    }

    void handle_locking_hard_drop() override
    {
        perform_action([this](){ locking_hard_drop(); });
    }

    void handle_no_locking_hard_drop() override
    {
        perform_action([this](){ no_locking_hard_drop(); });
    }

    void handle_hold() override
    {
        perform_action([this](){ hold(); });
    }

    void connect_reset_timeout(const std::function<void()> &handler) override
    {
        reset_timeout_.connect(handler);
    }

    void connect_set_timeout_delay(
        const std::function<void(int)> &handler) override
    {
        set_timeout_delay_.connect(handler);
    }

    unsigned long long get_score() const
    {
        return score_;
    }

    unsigned long long get_tetrises() const
    {
        return tetrises_;
    }

    Brick get_cur_brick() const
    {
        return cur_brick_;
    }

    Vector2 get_cur_brick_position() const
    {
        return cur_brick_position_;
    }

    int get_cur_brick_rotation() const
    {
        return cur_brick_rotation_;
    }

    Brick get_next_brick() const
    {
        return next_brick_;
    }

    Brick get_hold_brick() const
    {
        return hold_brick_;
    }

    bool get_can_hold() const
    {
        return can_hold_;
    }

    Settings get_settings() const
    {
        return settings_;
    }

    int get_lines_quantity() const
    {
        return lines_quantity_;
    }

    int get_level() const
    {
        return level_;
    }
    
private:
    using CubeMatrix = std::vector<std::vector<Cube>>;
    using Signal = boost::signals2::signal<void()>;
    using SignalInt = boost::signals2::signal<void(int)>;

    static constexpr int tetris_lines_quantity_{4};

    const Settings settings_;
    const Vector2 brick_start_position_;
    const int next_level_lines_quantity_;

    Ui::GameUi& ui_;
    Board& board_;
    BrickGenerator& brick_generator_;
    ScoreCounter& score_counter_;
    GameState state_;
    unsigned long long score_;
    unsigned long long tetrises_;
    Brick cur_brick_;
    Vector2 cur_brick_position_;
    int cur_brick_rotation_;
    Brick next_brick_;
    Brick hold_brick_;
    bool can_hold_;
    Signal reset_timeout_;
    SignalInt set_timeout_delay_;
    int lines_quantity_;
    int level_;

    void generate_hold_brick();
    void hold();
    void place(const Brick& brick);
    void place_and_generate_new_brick();
    bool brick_should_be_moved_up(const Brick& brick) const;
    Vector2 compute_spawn_position(const Brick& brick) const;
    int compute_lowest_position(const Brick& brick) const;
    bool can_rotate(
        const Brick& brick, Vector2 position, int rotation, int d_q) const;
    void tick();
    void rotate_clockwise();
    void rotate_counter_clockwise();
    void soft_drop();
    int hard_drop();
    void no_locking_hard_drop();
    Vector2 compute_ghost_brick_position() const;
    Brick create_ghost_brick() const;
    void draw_all();
    void refresh_ghost_brick(bool use_colors);
    void refresh_cur_brick(bool use_colors);
    void remove_lines(int from_y, int to_y);
    void generate_new_brick();
    void set_start_position_and_rotation();
    void add_score(unsigned long long amount);
    void add_lines(int amount);
    void add_tetrises(unsigned long long amount);
    void update_level();
    void perform_action(const std::function<void()>& action);

    void add_score_for_lines(int amount)
    {
        add_score(score_counter_.count_score_for_lines(amount));
        add_tetrises(amount / tetris_lines_quantity_);
    }

    bool can_move(const Brick& brick, Vector2 vector) const
    {
        return board_.brick_is_valid(Brick::get_translated(brick, vector));
    }

    void locking_hard_drop()
    {
        hard_drop();
        place_and_generate_new_brick();
    }

    void move_left()
    {
        if (can_move(get_transformed_cur_brick(), {-1, 0}))
            --cur_brick_position_.x;
    }

    void move_right()
    {
        if (can_move(get_transformed_cur_brick(), {1, 0}))
            ++cur_brick_position_.x;
    }

    void draw_bricks(bool use_colors = true)
    {
        refresh_ghost_brick(use_colors);
        refresh_cur_brick(use_colors);
    }

    void set_start_position()
    {
        cur_brick_position_ = compute_spawn_position(cur_brick_);
    }

    void set_start_rotation()
    {
        cur_brick_rotation_ = 0;
    }

    void check_if_game_ended()
    {
        if (not board_.brick_is_valid(get_transformed_cur_brick()))
            state_ = GameState::ended;
    }
};

}

#endif