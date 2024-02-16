#ifndef GAME_IMPL_H
#define GAME_IMPL_H

#include "board.h"
#include "brick_generator.h"
#include "game.h"
#include "game_state.h"
#include "game_ui.h"
#include "score_counter.h"
#include "vector_2.h"
#include <memory>

class GameImpl: public Game
{
    std::unique_ptr<GameUI> ui;
    std::unique_ptr<Board> board;
    std::unique_ptr<BrickGenerator> brick_generator;
    std::unique_ptr<ScoreCounter> score_counter;
    GameState state;
    int score;
    int tetrises;
    Brick cur_brick;
    Vector2 cur_brick_position;
    int cur_brick_rotation;
    Brick ghost_brick;
    Vector2 ghost_brick_position;
    Brick next_brick;
    Brick hold_brick;

    Vector2 get_brick_spawn_position(int brick_min_y, int board_width) const;
    void generate_new_brick();
    void refresh_ghost();
    void init_move();
    void commit_move();
    void move_down();

    public:
        GameImpl(
                std::unique_ptr<GameUI> &&ui,
                std::unique_ptr<Board> &&board,
                std::unique_ptr<BrickGenerator> &&brick_generator,
                std::unique_ptr<ScoreCounter> &&score_counter);
        void set_state(GameState state) override;
        GameState get_state() const override;
        void tick() override;
        void move_left() override;
        void move_right() override;
        void rotate() override;
        void soft_drop() override;
        void hard_drop() override;
        void hold() override;
        
        vector<vector<Pixel>> get_board_pixels() const;
        int get_score() const;
        int get_tetrises() const;
        Brick get_cur_brick() const;
        Vector2 get_cur_brick_position() const;
        int get_cur_brick_rotation() const;
        Brick get_ghost_brick() const;
        Vector2 get_ghost_brick_position() const;
        Brick get_next_brick() const;
        Brick get_hold_brick() const;
        Brick get_transformed_cur_brick() const;
        Brick get_transformed_ghost_brick() const;
};

#endif