#include "game_impl.h"

#include <algorithm>

#include "board.h"
#include "brick_generator.h"
#include "brick.h"
#include "game_state.h"
#include "game_ui.h"
#include "score_counter.h"
#include "vector_2.h"

namespace Tetris
{

using std::swap;

void GameImpl::generate_new_brick()
{
    this->cur_brick = this->next_brick;
    this->next_brick = this->brick_generator.generate();
    this->cur_brick_rotation = 0;
    this->cur_brick_position = this->compute_cur_brick_spawn_position(
        this->cur_brick.get_min_y(),
        this->board.get_width()
    );
    this->ui.draw_next(this->next_brick);
    if (not this->board.is_space_for_brick(this->get_transformed_cur_brick()))
        this->state = GameState::ended;
}

int GameImpl::compute_max_brick_move_vector_y(const Brick& brick) const
{
    int y{};
    while (this->board.is_space_for_brick(
        Brick::get_translated(brick, {0, y + 1})
    ))
        ++y;
    return y;
}

void GameImpl::update_ghost()
{
    this->ghost_brick = Brick::get_ghostified(this->cur_brick);
    this->ghost_brick_position = this->cur_brick_position;
    this->ghost_brick_position.y += this->compute_max_brick_move_vector_y(
        this->get_transformed_ghost_brick()
    );
}

void GameImpl::paste_bricks()
{
    this->update_ghost();
    this->board.paste_pixels(this->get_transformed_ghost_brick().pixels);
    this->board.paste_pixels(this->get_transformed_cur_brick().pixels);
    this->ui.draw_board(this->board.get_pixels());
}

void GameImpl::handle_tick()
{
    this->cut_bricks();
    if (this->can_move_brick_by(this->get_transformed_cur_brick(), {0, 1}))
        ++this->cur_brick_position.y;
    else
        this->place_and_generate_cur_brick();
    this->paste_bricks();
}

void GameImpl::remove_lines(int from_y, int to_y)
{
    const int lines{this->board.remove_lines_in_range_and_compress(
        from_y, to_y
    )};
    this->add_score(this->score_counter.count_score_for_lines(lines));
    this->add_tetrises(lines / tetris_line_count);
}

void GameImpl::place_and_generate_cur_brick()
{
    const Brick placed_brick{this->get_transformed_cur_brick()};
    this->board.paste_pixels(placed_brick.pixels);
    this->remove_lines(placed_brick.get_min_y(), placed_brick.get_max_y());
    this->generate_new_brick();
    this->can_hold = true;
}

void GameImpl::move_cur_brick_horizontally(int by)
{
    this->cut_bricks();
    if (this->can_move_brick_by(this->get_transformed_cur_brick(), {by, 0}))
        this->cur_brick_position.x += by;
    this->paste_bricks();
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
    this->paste_bricks();
    this->ui.draw_hold(this->hold_brick);
    this->ui.draw_score(this->score);
    this->ui.draw_tetrises(this->tetrises);
}

void GameImpl::handle_rotate()
{
    if (this->state != GameState::in_progress)
        return;

    this->cut_bricks();
    if (this->can_rotate_brick_by(
        Brick::get_rotated(this->cur_brick, this->cur_brick_rotation),
        this->cur_brick_position,
        1
    ))
        this->cur_brick_rotation = compute_quarters_rotation(
            this->cur_brick_rotation, 1
        );
        
    this->paste_bricks();
}

void GameImpl::handle_hard_drop()
{
    if (this->state != GameState::in_progress)
        return;

    this->cut_bricks();
    const int distance{this->compute_max_brick_move_vector_y(
        this->get_transformed_cur_brick()
    )};
    this->cur_brick_position.y += distance;
    this->place_and_generate_cur_brick();
    this->add_score(this->score_counter.count_score_for_hard_drop(distance));
    this->paste_bricks();
}

void GameImpl::handle_hold()
{
    if (this->state != GameState::in_progress)
        return;

    if (this->can_hold)
    {
        this->cut_bricks();
        swap(this->hold_brick, this->cur_brick);
        this->ui.draw_hold(this->hold_brick);
        if (this->cur_brick.empty())
            this->generate_new_brick();
        else
            this->cur_brick_position = this->compute_cur_brick_spawn_position(
                this->cur_brick.get_min_y(),
                this->board.get_width()
            );
        this->paste_bricks();
        this->can_hold = false;
    }
}

}