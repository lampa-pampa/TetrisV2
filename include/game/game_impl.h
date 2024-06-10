#ifndef INCLUDE_GAME_IMPL_H
#define INCLUDE_GAME_IMPL_H

#include "game/game.h"

#include <deque>
#include <functional>
#include <vector>

#include <boost/signals2.hpp>

#include "board/board.h"
#include "brick/brick.h"
#include "game/bricks.h"
#include "game/settings.h"
#include "game/stats.h"
#include "score_counter/score_counter.h"
#include "ui/game_ui/game_ui.h"
#include "vector_2/vector_2.h"

namespace Tetris
{

class GameImpl final: public Game
{
public:
    GameImpl(Ui::GameUi& ui,
        Board& board,
        ScoreCounter& score_counter,
        const GameBricks& bricks,
        const Settings& settings);

    GameImpl(const GameImpl&) = delete;
    GameImpl(const GameImpl&&) = delete;

    Brick get_transformed_cur_brick() const
    {
        return Brick::get_transformed(
            bricks_.cur.brick, bricks_.cur.rotation, bricks_.cur.position);
    }

    void resume() override
    {
        ui_.resume();
        ui_.flush_matrix();
        state_ = GameState::in_progress;
    }

    void pause() override
    {
        state_ = GameState::paused;
        ui_.pause();
        ui_.flush_matrix();
    }

    void game_over() override
    {
        ui_.game_over();
        ui_.flush_matrix();
    }

    GameState get_state() const override
    {
        return state_;
    }

    void handle_soft_drop() override
    {
        perform_action([this]() { soft_drop(); });
    }

    void handle_timeout() override
    {
        perform_action([this]() { tick(); });
    }

    void handle_move_left() override
    {
        perform_action([this]() { move_left(); });
    }

    void handle_move_right() override
    {
        perform_action([this]() { move_right(); });
    }

    void handle_rotate_clockwise() override
    {
        perform_action([this]() { rotate_clockwise(); });
    }

    void handle_rotate_counter_clockwise() override
    {
        perform_action([this]() { rotate_counter_clockwise(); });
    }

    void handle_locking_hard_drop() override
    {
        perform_action([this]() { locking_hard_drop(); });
    }

    void handle_no_locking_hard_drop() override
    {
        perform_action([this]() { no_locking_hard_drop(); });
    }

    void handle_hold() override
    {
        perform_action([this]() { hold(); });
    }

    void connect_reset_timeout(const std::function<void()>& handler) override
    {
        reset_timeout_.connect(handler);
    }

    void connect_set_timeout_delay(
        const std::function<void(int)>& handler) override
    {
        set_timeout_delay_.connect(handler);
    }

    unsigned long long get_score() const
    {
        return stats_.score;
    }

    unsigned long long get_tetrises() const
    {
        return stats_.tetrises;
    }

    Brick get_cur_brick() const
    {
        return bricks_.cur.brick;
    }

    Vector2 get_cur_brick_position() const
    {
        return bricks_.cur.position;
    }

    int get_cur_brick_rotation() const
    {
        return bricks_.cur.rotation;
    }

    std::deque<Brick> get_next_bricks() const
    {
        return bricks_.next;
    }

    Brick get_hold_brick() const
    {
        return bricks_.hold;
    }

    bool get_can_hold() const
    {
        return can_hold_;
    }

    Settings get_settings() const
    {
        return settings_;
    }

    int get_lines_count() const
    {
        return stats_.lines_count;
    }

    int get_level() const
    {
        return stats_.level;
    }

private:
    using CubeMatrix = std::vector<std::vector<Cube>>;
    using Signal = boost::signals2::signal<void()>;
    using SignalInt = boost::signals2::signal<void(int)>;

    static constexpr int tetris_lines_count_{4};
    static constexpr int next_level_lines_count_{10};

    Ui::GameUi& ui_;
    Board& board_;
    ScoreCounter& score_counter_;
    GameBricks bricks_;
    const Settings settings_;
    GameStats stats_;
    bool can_hold_;
    GameState state_;

    Signal reset_timeout_;
    SignalInt set_timeout_delay_;

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
    void update_level();
    void perform_action(const std::function<void()>& action);

    void add_score_for_lines(int amount)
    {
        add_score(score_counter_.count_score_for_lines(amount));
        stats_.tetrises += amount / tetris_lines_count_;
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
            --bricks_.cur.position.x;
    }

    void move_right()
    {
        if (can_move(get_transformed_cur_brick(), {1, 0}))
            ++bricks_.cur.position.x;
    }

    void draw_bricks(bool use_colors = true)
    {
        refresh_ghost_brick(use_colors);
        refresh_cur_brick(use_colors);
    }

    void set_start_position()
    {
        bricks_.cur.position = compute_spawn_position(bricks_.cur.brick);
    }

    void set_start_rotation()
    {
        bricks_.cur.rotation = 0;
    }

    void check_if_game_ended()
    {
        if (not board_.brick_is_valid(get_transformed_cur_brick()))
            state_ = GameState::ended;
    }
};

} // namespace Tetris

#endif
