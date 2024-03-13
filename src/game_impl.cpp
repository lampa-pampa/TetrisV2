#include "game_impl.h"

#include <algorithm>
#include <functional>
#include <vector>

#include "board.h"
#include "brick_generator.h"
#include "brick.h"
#include "settings.h"
#include "game_state.h"
#include "game_ui.h"
#include "score_counter.h"
#include "vector_2.h"

using std::function;
using std::swap;
using std::vector;

namespace Tetris
{
    GameImpl::GameImpl(
        GameUi& ui,
        Board& board,
        BrickGenerator& brick_generator,
        ScoreCounter& score_counter,
        int brick_start_position_y,
        Settings settings)
    :
        ui{ui},
        board{board},
        brick_generator{brick_generator},
        score_counter{score_counter},
        settings{settings},
        state{GameState::in_progress},
        score{0},
        tetrises{0},
        next_brick{this->brick_generator.generate()},
        hold_brick{},
        can_hold{true},
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

    Brick GameImpl::get_transformed_cur_brick() const
    {
        return Brick::get_transformed(
            this->cur_brick,
            this->cur_brick_rotation,
            this->cur_brick_position);
    }

    //-----------------------------------------------------------------

    void GameImpl::generate_hold_brick()
    {
        swap(this->hold_brick, this->cur_brick);
        this->ui.draw_hold_brick(this->hold_brick);
        if (this->cur_brick.empty())
            this->generate_new_brick();
    }

    void GameImpl::hold()
    {
        if (this->can_hold)
        {
            this->generate_hold_brick();
            this->set_start_position_and_rotation();
            this->can_hold = false;
        }
    }

    void GameImpl::place(const Brick& brick)
    {
        this->board.put_cubes(brick.cubes);
        this->remove_lines(brick.get_min_y(), brick.get_max_y());
        this->can_hold = true;
    }

    void GameImpl::place_and_generate_new_brick()
    {
        this->place(this->get_transformed_cur_brick());
        this->generate_new_brick();
        this->set_start_position_and_rotation();
    }

    bool GameImpl::brick_should_be_moved_up(const Brick& brick) const
    {
        return not this->board.brick_is_valid(brick)
            and brick.get_max_y() > this->board.get_offset()
            and brick.get_min_y() > 0;
    }
    
    Vector2 GameImpl::compute_spawn_position(const Brick& brick) const
    {
        Vector2 position{this->brick_start_position};
        while (this->brick_should_be_moved_up(
                Brick::get_translated(brick, position)))
            --position.y;
        return position;
    }

    int GameImpl::compute_lowest_position(const Brick& brick) const
    {
        int y{};
        while (this->board.brick_is_valid(
                Brick::get_translated(brick, {0, y + 1})))
            ++y;
        return y;
    }
    
    bool GameImpl::can_rotate(
        const Brick& brick, Vector2 position, int rotation, int d_q) const
    {
        const int next_rotation{Brick::compute_next_rotation(rotation, d_q)};
        return this->board.brick_is_valid(
            Brick::get_transformed(brick, next_rotation, position));
    }

    void GameImpl::try_to_perform_action(const function<void()>& action)
    {
        if (this->state == GameState::in_progress)
        {
            action();
            this->ui.draw_board(this->board.get_visible_cubes());
            this->draw_bricks();
        }            
    };

    void GameImpl::tick()
    {
        if (this->can_move(this->get_transformed_cur_brick(), {0, 1}))
            ++this->cur_brick_position.y;
        else
            this->place_and_generate_new_brick();
    }

    void GameImpl::rotate_clockwise()
    {
        if (this->can_rotate(
                this->cur_brick,
                this->cur_brick_position,
                this->cur_brick_rotation,
                1))
            this->cur_brick_rotation = Brick::compute_next_rotation(
                this->cur_brick_rotation, 1);
    }

    void GameImpl::rotate_counter_clockwise()
    {
        if (this->can_rotate(
                this->cur_brick,
                this->cur_brick_position,
                this->cur_brick_rotation,
                -1))
            this->cur_brick_rotation = Brick::compute_next_rotation(
                this->cur_brick_rotation, -1);
    }

    int GameImpl::hard_drop()
    {
        const int distance{this->compute_lowest_position(
            this->get_transformed_cur_brick())};
        this->cur_brick_position.y += distance;
        this->add_score(
            this->score_counter.count_score_for_hard_drop(distance));
        return distance;
    }

    void GameImpl::no_locking_hard_drop()
    {
        const int distance{this->hard_drop()};
        if(distance == 0)
            this->place_and_generate_new_brick();
    }

    Vector2 GameImpl::compute_ghost_brick_position() const
    {
        return {
            this->cur_brick_position.x,
            this->cur_brick_position.y + this->compute_lowest_position(
                this->get_transformed_cur_brick())
        };
    }

    Brick GameImpl::create_ghost_brick() const 
    {
        return Brick::get_transformed(
            this->cur_brick,
            this->cur_brick_rotation,
            this->compute_ghost_brick_position());
    }

    void GameImpl::draw_ghost_brick()
    {
        if (this->settings.generate_ghost)
        {
            this->ui.draw_ghost_brick(this->board.get_visible_brick_cubes(
                this->create_ghost_brick().cubes));
        }
    }

    void GameImpl::draw_bricks()
    {
        this->draw_ghost_brick();
        this->draw_cur_brick();
        this->ui.refresh();
    }

    void GameImpl::add_score_for_lines(int amount)
    {
        if (amount > 0)
        {
            this->add_score(this->score_counter.count_score_for_lines(amount));
            this->add_tetrises(amount / tetris_lines_quantity);
        }
    }

    void GameImpl::remove_lines(int from_y, int to_y)
    {
        const vector rows_with_line{
            this->board.remove_lines_and_compress(from_y, to_y)
        };
        this->add_score_for_lines(rows_with_line.size());
    }

    void GameImpl::generate_new_brick()
    {
        this->cur_brick = this->next_brick;
        this->next_brick = this->brick_generator.generate();
        this->ui.draw_next_brick(this->next_brick);
    }

    void GameImpl::set_start_position_and_rotation()
    {
        this->set_start_position();
        this->set_start_rotation();
        this->check_if_game_ended();
    }

    void GameImpl::add_score(unsigned long long amount)
    {
        if (amount > 0)
        {
            this->score += amount;
            this->ui.draw_score(this->score);
        }
    }

    void GameImpl::add_tetrises(unsigned long long amount)
    {
        if (amount > 0)
        {
            this->tetrises += amount;
            this->ui.draw_tetrises(this->tetrises);
        }
    }
}