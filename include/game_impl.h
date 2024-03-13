#ifndef INCLUDE_GAME_IMPL_H
#define INCLUDE_GAME_IMPL_H

#include "game.h"

#include <functional>
#include <gtest/gtest.h>
#include <vector>

#include "board.h"
#include "brick_generator.h"
#include "brick.h"
#include "settings.h"
#include "game_state.h"
#include "game_ui.h"
#include "score_counter.h"
#include "vector_2.h"

namespace Tetris
{

class GameImpl final: public Game
{
public:
    GameImpl(
        GameUi& ui,
        Board& board,
        BrickGenerator& brick_generator,
        ScoreCounter& score_counter,
        int brick_start_position_y,
        Settings settings);

    Brick get_transformed_cur_brick() const;

    void game_over() override
    {
        this->ui.game_over();
    }

    void pause() override
    {
        this->ui.pause();
        this->state = GameState::paused;
    }

    void resume() override
    {
        this->ui.resume();
        this->state = GameState::in_progress;
    }

    GameState get_state() const override
    {
        return this->state;
    }

    void handle_soft_drop() override
    {
        this->try_to_perform_action([this](){ this->soft_drop(); });
    }

    void handle_timeout() override
    {
        this->try_to_perform_action([this](){ this->tick(); });
    }

    void handle_move_left() override
    {
        this->try_to_perform_action([this](){ this->move_left(); });
    }

    void handle_move_right() override
    {
        this->try_to_perform_action([this](){ this->move_right(); });
    }

    void handle_rotate_clockwise() override
    {
        this->try_to_perform_action([this](){ this->rotate_clockwise(); });
    }

    void handle_rotate_counter_clockwise() override
    {
        this->try_to_perform_action([this](){
            this->rotate_counter_clockwise();});
    }

    void handle_locking_hard_drop() override
    {
        this->try_to_perform_action([this](){ this->locking_hard_drop(); });
    }

    void handle_no_locking_hard_drop() override
    {
        this->try_to_perform_action([this](){ this->no_locking_hard_drop(); });
    }

    void handle_hold() override
    {
        this->try_to_perform_action([this](){ this->hold(); });
    }

    unsigned long long get_score() const
    {
        return this->score;
    }

    unsigned long long get_tetrises() const
    {
        return this->tetrises;
    }

    Brick get_cur_brick() const
    {
        return this->cur_brick;
    }

    Vector2 get_cur_brick_position() const
    {
        return this->cur_brick_position;
    }

    int get_cur_brick_rotation() const
    {
        return this->cur_brick_rotation;
    }

    Brick get_next_brick() const
    {
        return this->next_brick;
    }

    Brick get_hold_brick() const
    {
        return this->hold_brick;
    }

    bool get_can_hold() const
    {
        return this->can_hold;
    }

    Settings get_settings() const
    {
        return this->settings;
    }
    
private:
    using CubeMatrix = std::vector<std::vector<Cube>>;

    static constexpr int tetris_lines_quantity{4};

    const Vector2 brick_start_position;

    GameUi& ui;
    Board& board;
    BrickGenerator& brick_generator;
    ScoreCounter& score_counter;
    Settings settings;
    GameState state;
    unsigned long long score;
    unsigned long long tetrises;
    Brick cur_brick;
    Vector2 cur_brick_position;
    int cur_brick_rotation;
    Brick next_brick;
    Brick hold_brick;
    bool can_hold;

    void generate_hold_brick();
    void hold();
    void place(const Brick& brick);
    void place_and_generate_new_brick();
    bool brick_should_be_moved_up(const Brick& brick) const;
    Vector2 compute_spawn_position(const Brick& brick) const;
    int compute_lowest_position(const Brick& brick) const;
    bool can_rotate(
        const Brick& brick, Vector2 position, int rotation, int d_q) const;
    void try_to_perform_action(const std::function<void()>& action);
    void tick();
    void rotate_clockwise();
    void rotate_counter_clockwise();
    int hard_drop();
    void no_locking_hard_drop();
    Vector2 compute_ghost_brick_position() const;
    Brick create_ghost_brick() const;
    void draw_ghost_brick();
    void draw_bricks();
    void add_score_for_lines(int amount);
    void remove_lines(int from_y, int to_y);
    void generate_new_brick();
    void set_start_position_and_rotation();
    void add_score(unsigned long long amount);
    void add_tetrises(unsigned long long amount);

    bool can_move(const Brick& brick, Vector2 vector) const
    {
        return this->board.brick_is_valid(
            Brick::get_translated(brick, vector));
    }

    Vector2 compute_brick_start_position(
        int board_width, int brick_start_position_y, int board_offset) const
    {
        return {(board_width - 1) / 2, brick_start_position_y + board_offset};
    }

    void soft_drop()
    {
        this->tick();
        this->add_score(this->score_counter.count_score_for_soft_drop());
    }

    void locking_hard_drop()
    {
        this->hard_drop();
        this->place_and_generate_new_brick();
    }

    void move_left()
    {
        if (this->can_move(this->get_transformed_cur_brick(), {-1, 0}))
            --this->cur_brick_position.x;
    }

    void move_right()
    {
        if (this->can_move(this->get_transformed_cur_brick(), {1, 0}))
            ++this->cur_brick_position.x;
    }

    void draw_cur_brick()
    {
        this->ui.draw_cur_brick(this->board.get_visible_brick_cubes(
            this->get_transformed_cur_brick().cubes));
    }

    void set_start_position()
    {
        this->cur_brick_position = this->compute_spawn_position(
            this->cur_brick);
    }

    void set_start_rotation()
    {
        this->cur_brick_rotation = 0;
    }

    void check_if_game_ended()
    {
        if (not this->board.brick_is_valid(this->get_transformed_cur_brick()))
            this->state = GameState::ended;
    }
};

}

#endif