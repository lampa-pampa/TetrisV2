#include "game_impl.h"
#include "brick.h"
#include "game_state.h"
#include "vector_2.h"
#include <memory>

using std::unique_ptr;

GameImpl::GameImpl(
    unique_ptr<GameUI> &&ui,
    unique_ptr<Board> &&board,
    unique_ptr<BrickGenerator> &&brick_generator,
    unique_ptr<ScoreCounter> &&score_counter)
:
    ui(std::move(ui)),
    board(std::move(board)),
    brick_generator(std::move(brick_generator)),
    score_counter(std::move(score_counter)),
    state(GameState::paused),
    score(0),
    tetrises(0),
    cur_brick(Brick{}),
    next_brick(this->brick_generator->generate()),
    cur_brick_rotation(0),
    cur_brick_position({0, 0}),
    ghost_brick(Brick{}),
    ghost_brick_position({0, 0}),
    hold_brick(Brick{})
{
    this->generate_new_brick();
    this->commit_move();
    this->ui->refresh_score(this->score);
    this->ui->refresh_tetrises(this->tetrises);
}

void GameImpl::set_state(GameState state)
{
    this->state = state;
}

GameState GameImpl::get_state() const
{
    return this->state;
}

void GameImpl::tick()
{
    this->move_down();
}

void GameImpl::move_left()
{
    
}

void GameImpl::move_right()
{
    
}

void GameImpl::rotate()
{
    
}

void GameImpl::soft_drop()
{
    this->move_down();
}

void GameImpl::hard_drop()
{
    
}

void GameImpl::hold()
{
    
}

/**************************************************************************************************************************************/

vector<vector<Pixel>> GameImpl::get_board_pixels() const
{
    return this->board->get_pixels();
}

int GameImpl::get_score() const
{
    return this->score;
}

int GameImpl::get_tetrises() const
{
    return this->tetrises;
}

Brick GameImpl::get_cur_brick() const
{
    return this->cur_brick;
}

Vector2 GameImpl::get_cur_brick_position() const
{
    return this->cur_brick_position;
}

int GameImpl::get_cur_brick_rotation() const
{
    return this->cur_brick_rotation;
}

Brick GameImpl::get_ghost_brick() const
{
    return this->ghost_brick;
}

Vector2 GameImpl::get_ghost_brick_position() const
{
    return this->ghost_brick_position;
}

Brick GameImpl::get_next_brick() const
{
    return this->next_brick;
}

Brick GameImpl::get_hold_brick() const
{
    return this->hold_brick;
}

Brick GameImpl::get_transformed_cur_brick() const
{
    return Brick::get_transformed(this->cur_brick, this->cur_brick_rotation, this->cur_brick_position);
}

Brick GameImpl::get_transformed_ghost_brick() const
{
    return Brick::get_transformed(this->ghost_brick, this->cur_brick_rotation, this->ghost_brick_position);
}

/**************************************************************************************************************************************/

Vector2 GameImpl::get_brick_spawn_position(int brick_min_y, int board_width) const
{
    return {(board_width - 1) / 2, -brick_min_y};
}

void GameImpl::refresh_ghost()
{
    this->ghost_brick = Brick::get_ghostified(this->cur_brick);
    this->ghost_brick_position = cur_brick_position;
    if(this->board->is_space_for_brick(this->get_transformed_ghost_brick()))
    {
        while(this->board->is_space_for_brick(this->get_transformed_ghost_brick()))
            ++this->ghost_brick_position.y;
        --this->ghost_brick_position.y;
    }
}

void GameImpl::init_move()
{
    this->board->remove_brick(this->get_transformed_ghost_brick());
    this->board->remove_brick(this->get_transformed_cur_brick());
}

void GameImpl::commit_move()
{
    refresh_ghost();
    this->board->add_brick(this->get_transformed_ghost_brick());
    this->board->add_brick(this->get_transformed_cur_brick());
    this->ui->refresh_board(this->board->get_pixels());
}

void GameImpl::generate_new_brick()
{
    this->cur_brick = std::move(this->next_brick);
    this->next_brick = this->brick_generator->generate();
    this->cur_brick_rotation = 0;
    this->cur_brick_position = this->get_brick_spawn_position(this->cur_brick.get_min_y(), this->board->get_width());
    this->ui->refresh_next(this->next_brick);
    if(not this->board->is_space_for_brick(this->get_transformed_cur_brick()))
        this->state = GameState::ended;
}

void GameImpl::move_down()
{
    
}