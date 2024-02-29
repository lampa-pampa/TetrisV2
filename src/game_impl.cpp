#include "board.h"
#include "brick_generator.h"
#include "brick.h"
#include "game_impl.h"
#include "game_state.h"
#include "game_ui.h"
#include "score_counter.h"
#include <algorithm>

namespace Tetris
{

using std::swap;

void GameImpl::generate_new_brick()
{
    this->cur_brick = std::move(this->next_brick);
    this->next_brick = this->brick_generator.generate();
    this->cur_brick_rotation = 0;
    this->cur_brick_position = this->get_brick_spawn_position(
        this->cur_brick.get_min_y(),
        this->board.get_width()
    );
    this->ui.refresh_next(this->next_brick);
    if (not this->board.is_space_for_brick(this->get_transformed_cur_brick()))
        this->state = GameState::ended;
}

void GameImpl::refresh_ghost()
{
    this->ghost_brick = Brick::get_ghostified(this->cur_brick);
    this->ghost_brick_position = this->cur_brick_position;
    if (this->board.is_space_for_brick(this->get_transformed_ghost_brick()))
    {
        while(this->board.is_space_for_brick(
            this->get_transformed_ghost_brick()
        ))
            ++this->ghost_brick_position.y;
        
        --this->ghost_brick_position.y;
    }
}

void GameImpl::commit_move()
{
    this->refresh_ghost();
    this->board.add_brick(this->get_transformed_ghost_brick());
    this->board.add_brick(this->get_transformed_cur_brick());
    this->ui.refresh_board(this->board.get_pixels());
}

void GameImpl::move_down()
{
    this->init_move();
    ++this->cur_brick_position.y;
    if (not this->board.is_space_for_brick(this->get_transformed_cur_brick()))
    {
        --this->cur_brick_position.y;
        this->place_and_generate_cur_brick();
    }
    this->commit_move();
}

void GameImpl::remove_lines(int from_y, int to_y)
{
    const int lines = this->board.remove_lines_in_range_and_compress(
        from_y,
        to_y
    );
    if (lines > 0)
    {
        this->add_score(this->score_counter.count_score_for_lines(lines));
        if (lines == 4)
        {
            this->tetrises += 1;
            this->ui.refresh_tetrises(this->tetrises);
        }
    }
}

void GameImpl::place_and_generate_cur_brick()
{
    Brick placed_brick{this->get_transformed_cur_brick()};
    this->board.add_brick(placed_brick);
    this->remove_lines(placed_brick.get_min_y(), placed_brick.get_max_y());
    this->generate_new_brick();
    this->can_hold = true;
}

void GameImpl::move_cur_brick_horizontally(int by)
{
    this->init_move();
    int old_position = this->cur_brick_position.x;
    this->cur_brick_position.x += by;
    if (not this->board.is_space_for_brick(this->get_transformed_cur_brick()))
        this->cur_brick_position.x = old_position;
    this->commit_move();   
}

GameImpl::GameImpl(
    GameUi& ui,
    Board& board,
    BrickGenerator& brick_generator,
    ScoreCounter& score_counter
):
    ui{ui},
    board{board},
    brick_generator{brick_generator},
    score_counter{score_counter},
    state{GameState::in_progress},
    score{0},
    tetrises{0},
    next_brick{this->brick_generator.generate()},
    cur_brick_rotation{0},
    can_hold{true}
{
    this->generate_new_brick();
    this->commit_move();
    this->ui.refresh_hold(this->hold_brick);
    this->ui.refresh_score(this->score);
    this->ui.refresh_tetrises(this->tetrises);
}

void GameImpl::handle_rotate()
{
    this->init_move();
    int old_rotation = this->cur_brick_rotation;
    this->cur_brick_rotation = (this->cur_brick_rotation + 1) % (Brick::rotation_quantity);
    if (not this->board.is_space_for_brick(this->get_transformed_cur_brick()))
        this->cur_brick_rotation = old_rotation;
    this->commit_move();
}

void GameImpl::handle_hard_drop()
{
    this->init_move();
    int distance{};
    while(this->board.is_space_for_brick(this->get_transformed_cur_brick()))
    {
        ++distance;
        ++this->cur_brick_position.y;
    }
    --this->cur_brick_position.y;
    this->place_and_generate_cur_brick();
    this->add_score(this->score_counter.count_score_for_hard_drop(distance));
    this->commit_move();
}

void GameImpl::handle_hold()
{
    if (this->can_hold)
    {
        this->init_move();
        swap(this->hold_brick, this->cur_brick);
        this->ui.refresh_hold(this->hold_brick);
        if (this->cur_brick.empty())
            this->generate_new_brick();
        else
            this->cur_brick_position = this->get_brick_spawn_position(
                this->cur_brick.get_min_y(),
                this->board.get_width()
            );
        this->commit_move();
        this->can_hold = false;
    }
}

}