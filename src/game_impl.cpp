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

Vector2 GameImpl::compute_spawn_position(const Brick& brick) const
{
    Vector2 position{brick_start_position};
    Brick translated_brick{brick};
    while (
            not this->board.brick_is_valid(
                translated_brick = Brick::get_translated(brick, position))
            and translated_brick.get_max_y() > this->config.board_offset
            and translated_brick.get_min_y() > 0)
        --position.y;
    return position;
}

void GameImpl::hold()
{
    if (not this->can_hold)
        return;
    
    swap(this->hold_brick, this->cur_brick);
    this->ui.draw_hold(this->hold_brick);
    if (this->cur_brick.empty())
        this->generate_new_brick();
    this->set_start_position_and_rotation();
    this->can_hold = false;
}

void GameImpl::place_and_generate_cur_brick()
{
    const Brick placed_brick{this->get_transformed_cur_brick()};
    this->board.put_cubes(placed_brick.cubes);
    this->remove_lines(placed_brick.get_min_y(), placed_brick.get_max_y());
    this->generate_new_brick();
    this->set_start_position_and_rotation();
    this->can_hold = true;
}

GameImpl::GameImpl(
    GameConfig config,
    GameUi& ui,
    Board& board,
    BrickGenerator& brick_generator,
    ScoreCounter& score_counter)
:
    config{config},
    ui{ui},
    board{board},
    brick_generator{brick_generator},
    score_counter{score_counter},
    state{GameState::in_progress},
    score{0},
    tetrises{0},
    hold_brick{},
    next_brick{this->brick_generator.generate()},
    can_hold{true},
    brick_start_position{
        (board.get_width() - 1) / 2,
        this->config.brick_start_position_y}
{
    this->generate_new_brick();
    this->set_start_position_and_rotation();
    this->put_bricks_on_board();
    this->ui.draw_hold(this->hold_brick);
    this->ui.draw_score(this->score);
    this->ui.draw_tetrises(this->tetrises);
}

}