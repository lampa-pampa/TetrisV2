#ifndef INCLUDE_GAME_IMPL_H
#define INCLUDE_GAME_IMPL_H

#include <functional>
#include <vector>

#include "board.h"
#include "brick_generator.h"
#include "brick.h"
#include "config.h"
#include "game_state.h"
#include "game_ui.h"
#include "game.h"
#include "score_counter.h"
#include "vector_2.h"

namespace Tetris
{

class GameImpl final: public Game
{
    using CubeMatrix = std::vector<std::vector<Cube>>;

    const GameConfig config;
    const Vector2 brick_start_position;

    GameUi& ui;
    Board& board;
    BrickGenerator& brick_generator;
    ScoreCounter& score_counter;
    GameState state;
    unsigned long long score;
    unsigned long long tetrises;
    Brick cur_brick;
    Vector2 cur_brick_position;
    int cur_brick_rotation;
    Brick ghost_brick;
    Vector2 ghost_brick_position;
    Brick next_brick;
    Brick hold_brick;
    bool can_hold;

    Vector2 compute_spawn_position(const Brick& brick) const;
    void hold();
    void place_and_generate_cur_brick();
    void move_cur_brick_horizontally(int d_x);

    int compute_lowest_position(const Brick& brick) const
    {
        int y{};
        while (this->board.brick_is_valid(
                Brick::get_translated(brick, {0, y + 1})))
            ++y;
        return y;
    }

    bool can_move(const Brick& brick, Vector2 vector) const
    {
        return this->board.brick_is_valid(
            Brick::get_translated(brick, vector));
    }
    
    bool can_rotate(
        const Brick& brick, Vector2 position, int rotation, int d_q) const
    {
        const int next_rotation{this->compute_next_rotation(rotation, d_q)};
        return this->board.brick_is_valid(
            Brick::get_transformed(brick, next_rotation, position));
    }

    int compute_next_rotation(int rotation, int d_q) const
    {
        return (rotation + d_q + Brick::rotation_quantity)
            % Brick::rotation_quantity;
    }

    void try_to_perform_action(const std::function<void()>& action)
    {
        if (this->state != GameState::in_progress)
            return;
        this->remove_bricks_from_board();
        action();
        this->put_bricks_on_board();
    };

    void tick()
    {
        if (this->can_move(this->get_transformed_cur_brick(), {0, 1}))
            ++this->cur_brick_position.y;
        else
            this->place_and_generate_cur_brick();
    }

    void rotate_clockwise()
    {
        if (this->can_rotate(
                Brick::get_rotated(this->cur_brick, this->cur_brick_rotation),
                this->cur_brick_position,
                this->cur_brick_rotation,
                -1))
            this->cur_brick_rotation = compute_next_rotation(
                this->cur_brick_rotation, 1);
    }

    void rotate_counter_clockwise()
    {
        if (this->can_rotate(
                Brick::get_rotated(this->cur_brick, this->cur_brick_rotation),
                this->cur_brick_position,
                this->cur_brick_rotation,
                -1))
            this->cur_brick_rotation = compute_next_rotation(
                this->cur_brick_rotation, -1);
    }

    void hard_drop()
    {
        const int distance{this->compute_lowest_position(
            this->get_transformed_cur_brick())};
        this->cur_brick_position.y += distance;
        this->place_and_generate_cur_brick();
        this->add_score(
            this->score_counter.count_score_for_hard_drop(distance));
    }

    void soft_drop()
    {
        this->tick();
        this->add_score(this->score_counter.count_score_for_soft_drop());
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

    void update_ghost()
    {
        this->ghost_brick = Brick::get_ghostified(this->cur_brick);
        this->ghost_brick_position = this->cur_brick_position;
        this->ghost_brick_position.y += this->compute_lowest_position(
            this->get_transformed_ghost_brick());
    }

    void put_bricks_on_board()
    {
        this->update_ghost();
        this->board.put_cubes(this->get_transformed_ghost_brick().cubes);
        this->board.put_cubes(this->get_transformed_cur_brick().cubes);
        this->ui.draw_board(this->board.get_cubes(this->config.board_offset));
    }

    void remove_lines(int from_y, int to_y)
    {
        const int lines{this->board.remove_lines_and_compress(from_y, to_y)};
        this->add_score(this->score_counter.count_score_for_lines(lines));
        this->add_tetrises(lines / this->config.tetris_line_count);
    }

    void generate_new_brick()
    {
        this->cur_brick = this->next_brick;
        this->next_brick = this->brick_generator.generate();
        this->ui.draw_next(this->next_brick);
    }

    void set_start_position_and_rotation()
    {
        this->cur_brick_position = this->compute_spawn_position(
            this->cur_brick);
        this->cur_brick_rotation = 0;
        if (not this->board.brick_is_valid(this->get_transformed_cur_brick()))
            this->state = GameState::ended;
    }

    void remove_bricks_from_board()
    {
        this->board.clear_cubes(this->get_transformed_ghost_brick().cubes);
        this->board.clear_cubes(this->get_transformed_cur_brick().cubes);
    }

    void add_score(unsigned long long amount)
    {
        if (amount > 0)
        {
            this->score += amount;
            this->ui.draw_score(this->score);
        }
    }

    void add_tetrises(unsigned long long amount)
    {
        if (amount > 0)
        {
            this->tetrises += amount;
            this->ui.draw_tetrises(this->tetrises);
        }
    }

public:
    GameImpl(
        GameConfig config,
        GameUi& ui,
        Board& board,
        BrickGenerator& brick_generator,
        ScoreCounter& score_counter);

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

    void handle_hard_drop() override
    {
        this->try_to_perform_action([this](){ this->hard_drop(); });
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

    Brick get_ghost_brick() const
    {
        return this->ghost_brick;
    }

    Vector2 get_ghost_brick_position() const
    {
        return this->ghost_brick_position;
    }

    Brick get_next_brick() const
    {
        return this->next_brick;
    }

    Brick get_hold_brick() const
    {
        return this->hold_brick;
    }

    Brick get_transformed_cur_brick() const
    {
        return Brick::get_transformed(
            this->cur_brick,
            this->cur_brick_rotation,
            this->cur_brick_position);
    }

    Brick get_transformed_ghost_brick() const
    {
        return Brick::get_transformed(
            this->ghost_brick,
            this->cur_brick_rotation,
            this->ghost_brick_position);
    }
};

}

#endif