#ifndef INCLUDE_GAME_IMPL_H
#define INCLUDE_GAME_IMPL_H

#include "game.h"

#include <functional>
#include <gtest/gtest.h>
#include <vector>

#include "board.h"
#include "brick_generator.h"
#include "brick.h"
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
        bool generate_ghost)
    :
        ui{ui},
        board{board},
        brick_generator{brick_generator},
        score_counter{score_counter},
        state{GameState::in_progress},
        score{0},
        tetrises{0},
        next_brick{this->brick_generator.generate()},
        hold_brick{},
        can_hold{true},
        generate_ghost{generate_ghost},
        brick_start_position{this->compute_brick_start_position(
            board.get_width(), brick_start_position_y, board.get_offset())
        }
    {
        this->ui.draw_hold_brick(this->hold_brick);
        this->ui.draw_score(this->score);
        this->ui.draw_tetrises(this->tetrises);
        this->ui.draw_board(this->board.get_visible_cubes());
        this->generate_new_brick();
        this->set_start_position_and_rotation();
        this->draw_bricks();
    }

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

    bool get_generate_ghost() const
    {
        return this->generate_ghost;
    }

    Brick get_transformed_cur_brick() const
    {
        return Brick::get_transformed(
            this->cur_brick,
            this->cur_brick_rotation,
            this->cur_brick_position);
    }
    
private:
    using CubeMatrix = std::vector<std::vector<Cube>>;

    static constexpr int tetris_lines_quantity{4};

    const Vector2 brick_start_position;
    const bool generate_ghost;

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
    Brick next_brick;
    Brick hold_brick;
    bool can_hold;

    Vector2 compute_brick_start_position(
        int board_width, int brick_start_position_y, int board_offset) const
    {
        return {(board_width - 1) / 2,
            brick_start_position_y + board_offset};
    }

    void generate_hold_brick()
    {
        std::swap(this->hold_brick, this->cur_brick);
        this->ui.draw_hold_brick(this->hold_brick);
        if (this->cur_brick.empty())
            this->generate_new_brick();
    }

    void hold()
    {
        if (this->can_hold)
        {
            this->generate_hold_brick();
            this->set_start_position_and_rotation();
            this->can_hold = false;
        }
    }

    void place(const Brick& brick)
    {
        this->board.put_cubes(brick.cubes);
        this->remove_lines(brick.get_min_y(), brick.get_max_y());
        this->can_hold = true;
    }

    void place_and_generate_new_brick()
    {
        this->place(this->get_transformed_cur_brick());
        this->generate_new_brick();
        this->set_start_position_and_rotation();
    }

    bool brick_should_be_moved_up(const Brick& brick) const
    {
        return not this->board.brick_is_valid(brick)
            and brick.get_max_y() > this->board.get_offset()
            and brick.get_min_y() > 0;
    }
    
    Vector2 compute_spawn_position(const Brick& brick) const
    {
        Vector2 position{this->brick_start_position};
        while (this->brick_should_be_moved_up(
                Brick::get_translated(brick, position)))
            --position.y;
        return position;
    }

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
        const int next_rotation{Brick::compute_next_rotation(rotation, d_q)};
        return this->board.brick_is_valid(
            Brick::get_transformed(brick, next_rotation, position));
    }

    void try_to_perform_action(const std::function<void()>& action)
    {
        if (this->state == GameState::in_progress)
        {
            action();
            this->ui.draw_board(this->board.get_visible_cubes());
            this->draw_bricks();
        }            
    };

    void tick()
    {
        if (this->can_move(this->get_transformed_cur_brick(), {0, 1}))
            ++this->cur_brick_position.y;
        else
            this->place_and_generate_new_brick();
    }

    void rotate_clockwise()
    {
        if (this->can_rotate(
                this->cur_brick,
                this->cur_brick_position,
                this->cur_brick_rotation,
                1))
            this->cur_brick_rotation = Brick::compute_next_rotation(
                this->cur_brick_rotation, 1);
    }

    void rotate_counter_clockwise()
    {
        if (this->can_rotate(
                this->cur_brick,
                this->cur_brick_position,
                this->cur_brick_rotation,
                -1))
            this->cur_brick_rotation = Brick::compute_next_rotation(
                this->cur_brick_rotation, -1);
    }

    void hard_drop()
    {
        const int distance{this->compute_lowest_position(
            this->get_transformed_cur_brick())};
        this->cur_brick_position.y += distance;
        this->place_and_generate_new_brick();
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

    Vector2 compute_ghost_brick_position() const
    {
        return {
            this->cur_brick_position.x,
            this->cur_brick_position.y + this->compute_lowest_position(
                this->get_transformed_cur_brick())
        };
    }

    Brick create_ghost_brick() const 
    {
        return Brick::get_transformed(
            this->cur_brick,
            this->cur_brick_rotation,
            this->compute_ghost_brick_position());
    }

    void draw_ghost_brick()
    {
        if (this->generate_ghost)
        {
            this->ui.draw_ghost_brick(this->board.get_visible_brick_cubes(
                this->create_ghost_brick().cubes));
        }
    }

    void draw_cur_brick()
    {
        this->ui.draw_cur_brick(this->board.get_visible_brick_cubes(
            this->get_transformed_cur_brick().cubes));
    }

    void draw_bricks()
    {
        this->draw_ghost_brick();
        this->draw_cur_brick();
        this->ui.refresh();
    }

    void add_score_for_lines(int amount)
    {
        if (amount > 0)
        {
            this->add_score(this->score_counter.count_score_for_lines(amount));
            this->add_tetrises(amount / tetris_lines_quantity);
        }
    }

    void remove_lines(int from_y, int to_y)
    {
        const std::vector rows_with_line{
            this->board.remove_lines_and_compress(from_y, to_y)
        };
        this->add_score_for_lines(rows_with_line.size());
    }

    void generate_new_brick()
    {
        this->cur_brick = this->next_brick;
        this->next_brick = this->brick_generator.generate();
        this->ui.draw_next_brick(this->next_brick);
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

    void set_start_position_and_rotation()
    {
        this->set_start_position();
        this->set_start_rotation();
        this->check_if_game_ended();
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
};

}

#endif