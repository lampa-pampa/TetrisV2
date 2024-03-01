#ifndef INCLUDE_GAME_IMPL_H
#define INCLUDE_GAME_IMPL_H

#include <vector>

#include "board.h"
#include "brick_generator.h"
#include "brick.h"
#include "game_state.h"
#include "game_ui.h"
#include "game.h"
#include "score_counter.h"
#include "vector_2.h"

namespace Tetris
{

class GameImpl final: public Game
{
    using Pixels = std::vector<std::vector<Pixel>>;

    GameUi& ui;
    Board& board;
    BrickGenerator& brick_generator;
    ScoreCounter& score_counter;
    GameState state;
    unsigned long long score;
    unsigned long long tetrises;
    Brick cur_brick;
    Vector2 cur_brick_position;
    unsigned short cur_brick_rotation;
    Brick ghost_brick;
    Vector2 ghost_brick_position;
    Brick next_brick;
    Brick hold_brick;
    bool can_hold;

    void generate_new_brick();
    void refresh_ghost();
    void commit_move();
    void move_down();
    void remove_lines(int from_y, int to_y);
    void place_and_generate_cur_brick();
    void move_cur_brick_horizontally(int by);
 
    void init_move()
    {
        this->board.remove_brick(this->get_transformed_ghost_brick());
        this->board.remove_brick(this->get_transformed_cur_brick());
    }

    Vector2 get_brick_spawn_position(int brick_min_y, int board_width) const
    {
        return {(board_width - 1) / 2, -brick_min_y};
    }

    void add_score(unsigned long long amount)
    {
        this->score += amount;
        this->ui.refresh_score(this->score);
    }

public:
    GameImpl(
        GameUi& ui,
        Board& board,
        BrickGenerator& brick_generator,
        ScoreCounter& score_counter
    );

    void handle_rotate() override;
    void handle_hard_drop() override;
    void handle_hold() override;

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

    void handle_soft_drop() override
    {
        if (this->state != GameState::in_progress)
            return;

        this->move_down();
        this->add_score(this->score_counter.count_score_for_soft_drop());
    }

    GameState get_state() const override
    {
        return this->state;
    }

    void handle_tick() override
    {
        if (this->state != GameState::in_progress)
            return;

        this->move_down();
    }

    void handle_move_left() override
    {
        if (this->state != GameState::in_progress)
            return;

        this->move_cur_brick_horizontally(-1);
    }

    void handle_move_right() override
    {
        if (this->state != GameState::in_progress)
            return;

        this->move_cur_brick_horizontally(1);
    }
    
    Pixels get_board_pixels() const
    {
        return this->board.get_pixels();
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

    unsigned short get_cur_brick_rotation() const
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
            this->cur_brick_position
        );
    }

    Brick get_transformed_ghost_brick() const
    {
        return Brick::get_transformed(
            this->ghost_brick,
            this->cur_brick_rotation,
            this->ghost_brick_position
        );
    }
};

}

#endif