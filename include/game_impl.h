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
        int brick_start_position_y,
        Settings settings);

        GameImpl(const GameImpl&) = delete;
        GameImpl(const GameImpl&&) = delete;

    Brick get_transformed_cur_brick() const;

    void pause() override
    {
        this->ui.pause();
        this->state = GameState::paused;
    }

    void resume() override
    {
        this->draw_board_and_bricks();
        this->state = GameState::in_progress;
    }

    void game_over() override
    {
        this->ui.game_over();
    }

    GameState get_state() const override
    {
        return this->state;
    }

    void handle_soft_drop() override
    {
        this->perform_action([this](){ this->soft_drop(); });
    }

    void handle_timeout() override
    {
        this->perform_action([this](){ this->tick(); });
    }

    void handle_move_left() override
    {
        this->perform_action([this](){ this->move_left(); });
    }

    void handle_move_right() override
    {
        this->perform_action([this](){ this->move_right(); });
    }

    void handle_rotate_clockwise() override
    {
        this->perform_action([this](){ this->rotate_clockwise(); });
    }

    void handle_rotate_counter_clockwise() override
    {
        this->perform_action([this](){this->rotate_counter_clockwise();});
    }

    void handle_locking_hard_drop() override
    {
        this->perform_action([this](){ this->locking_hard_drop(); });
    }

    void handle_no_locking_hard_drop() override
    {
        this->perform_action([this](){ this->no_locking_hard_drop(); });
    }

    void handle_hold() override
    {
        this->perform_action([this](){ this->hold(); });
    }

    void connect_reset_timeout(const std::function<void()> &handler) override
    {
        this->reset_timeout.connect(handler);
    }

    void connect_set_timeout_delay(
        const std::function<void(int)> &handler) override
    {
        this->set_timeout_delay.connect(handler);
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

    int get_lines_quantity() const
    {
        return this->lines_quantity;
    }

    int get_level() const
    {
        return this->level;
    }
    
private:
    using CubeMatrix = std::vector<std::vector<Cube>>;
    using Signal = boost::signals2::signal<void()>;
    using SignalInt = boost::signals2::signal<void(int)>;

    static constexpr int tetris_lines_quantity{4};
    static constexpr int next_level_lines_quantity{10};

    const Vector2 brick_start_position;

    Ui::GameUi& ui;
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
    Signal reset_timeout;
    SignalInt set_timeout_delay;
    int lines_quantity;
    int level;

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
    void draw_ghost_brick();
    void remove_lines(int from_y, int to_y);
    void generate_new_brick();
    void set_start_position_and_rotation();
    void add_score(unsigned long long amount);
    void add_lines(int amount);
    void update_level();
    void draw_board_and_bricks();

    void perform_action(const std::function<void()>& action)
    {
        action();
        this->draw_bricks();
        this->ui.refresh();       
    };

    void add_score_for_lines(int amount)
    {
        this->add_score(this->score_counter.count_score_for_lines(amount));
        this->add_tetrises(amount / tetris_lines_quantity);
    }

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

    void draw_bricks()
    {
        this->draw_ghost_brick();
        this->draw_cur_brick();
    }

    void draw_cur_brick()
    {
        this->ui.draw_cur_brick(this->board.get_visible_brick_cubes(
            this->get_transformed_cur_brick().cubes));
    }

    void add_tetrises(unsigned long long amount)
    {
        if (amount > 0)
            this->tetrises += amount;
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