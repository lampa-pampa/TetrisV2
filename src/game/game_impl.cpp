#include "game/game_impl.h"

#include <algorithm>
#include <vector>

#include <boost/range/irange.hpp>

#include "board/board.h"
#include "brick/bag.h"
#include "brick/brick.h"
#include "brick/brick_name.h"
#include "game/game_state.h"
#include "game/settings.h"
#include "score_counter/score_counter.h"
#include "ui/game_ui/game_ui.h"
#include "vector_2/vector_2.h"

using std::function;
using std::swap;
using std::vector;

namespace Tetris
{

GameImpl::GameImpl(Ui::GameUi& ui,
    Board& board,
    Bag<Brick>& bricks_bag,
    ScoreCounter& score_counter,
    const Settings& settings,
    Vector2 brick_start_position,
    int next_level_lines_count)
  : ui_{ui},
    board_{board},
    bricks_bag_{bricks_bag},
    score_counter_{score_counter},
    settings_{settings},
    brick_start_position_{brick_start_position},
    next_level_lines_count_{next_level_lines_count},
    state_{GameState::in_progress},
    score_{},
    tetrises_{},
    level_{settings.start_level},
    lines_count_{},
    hold_brick_{},
    can_hold_{true}
{
    for (const auto& i : boost::irange(next_bricks_count))
        next_bricks_.emplace_back(bricks_bag_.get_next());
    generate_new_brick();
    set_start_position_and_rotation();
    draw_all();
}

//-----------------------------------------------------------------

void GameImpl::generate_hold_brick()
{
    swap(hold_brick_, cur_brick_);
    ui_.refresh_hold_brick(hold_brick_);
    if (cur_brick_.empty())
        generate_new_brick();
}

void GameImpl::hold()
{
    if (can_hold_)
    {
        generate_hold_brick();
        set_start_position_and_rotation();
        can_hold_ = false;
        reset_timeout_();
    }
}

void GameImpl::place(const Brick& brick)
{
    board_.put_cubes(brick.get_cubes());
    remove_lines(brick.get_min_y(), brick.get_max_y());
    ui_.refresh_board(board_.get_cubes());
    can_hold_ = true;
}

void GameImpl::place_and_generate_new_brick()
{
    place(get_transformed_cur_brick());
    generate_new_brick();
    set_start_position_and_rotation();
}

bool GameImpl::brick_should_be_moved_up(const Brick& brick) const
{
    return not board_.brick_is_valid(brick) and brick.get_min_y() > 0;
}

Vector2 GameImpl::compute_spawn_position(const Brick& brick) const
{
    Vector2 position{brick_start_position_};
    while (brick_should_be_moved_up(Brick::get_translated(brick, position)))
        --position.y;
    return position;
}

int GameImpl::compute_lowest_position(const Brick& brick) const
{
    int y{};
    while (board_.brick_is_valid(Brick::get_translated(brick, {0, y + 1})))
        ++y;
    return y;
}

bool GameImpl::can_rotate(
    const Brick& brick, Vector2 position, int rotation, int d_q) const
{
    const int next_rotation{Brick::compute_next_rotation(rotation, d_q)};
    return board_.brick_is_valid(
        Brick::get_transformed(brick, next_rotation, position));
}

void GameImpl::tick()
{
    if (can_move(get_transformed_cur_brick(), {0, 1}))
        ++cur_brick_position_.y;
    else
        place_and_generate_new_brick();
}

void GameImpl::rotate_clockwise()
{
    if (can_rotate(cur_brick_, cur_brick_position_, cur_brick_rotation_, 1))
        cur_brick_rotation_ =
            Brick::compute_next_rotation(cur_brick_rotation_, 1);
}

void GameImpl::rotate_counter_clockwise()
{
    if (can_rotate(cur_brick_, cur_brick_position_, cur_brick_rotation_, -1))
        cur_brick_rotation_ =
            Brick::compute_next_rotation(cur_brick_rotation_, -1);
}

int GameImpl::hard_drop()
{
    const int distance{compute_lowest_position(get_transformed_cur_brick())};
    cur_brick_position_.y += distance;
    add_score(score_counter_.count_score_for_hard_drop(distance));
    reset_timeout_();
    return distance;
}

void GameImpl::soft_drop()
{
    tick();
    add_score(score_counter_.count_score_for_soft_drop());
    reset_timeout_();
}

void GameImpl::no_locking_hard_drop()
{
    const int distance{hard_drop()};
    if (distance == 0)
        place_and_generate_new_brick();
}

Vector2 GameImpl::compute_ghost_brick_position() const
{
    return {cur_brick_position_.x,
        cur_brick_position_.y
            + compute_lowest_position(get_transformed_cur_brick())};
}

Brick GameImpl::create_ghost_brick() const
{
    return Brick::get_transformed(
        cur_brick_, cur_brick_rotation_, compute_ghost_brick_position());
}

void GameImpl::draw_all()
{
    ui_.refresh_background();
    ui_.refresh_hold_brick(hold_brick_);
    ui_.refresh_level_progress_bar(lines_count_);
    ui_.refresh_level(level_);
    ui_.refresh_board(board_.get_cubes());
    ui_.refresh_next_bricks(next_bricks_);
    ui_.refresh_score(score_);
    draw_bricks();
    ui_.flush_matrix();
}

void GameImpl::refresh_ghost_brick(bool use_colors)
{
    if (settings_.generate_ghost)
    {
        Brick brick = create_ghost_brick();
        if (not use_colors)
            brick.name = BrickName::empty;
        ui_.refresh_ghost_brick(
            board_.get_visible_brick_cubes(brick.get_cubes()));
    }
}

void GameImpl::refresh_cur_brick(bool use_colors)
{
    Brick brick = get_transformed_cur_brick();
    if (not use_colors)
        brick.name = BrickName::empty;
    ui_.refresh_cur_brick(board_.get_visible_brick_cubes(brick.get_cubes()));
}

void GameImpl::remove_lines(int from_y, int to_y)
{
    const vector rows_with_line{board_.remove_lines_and_compress(from_y, to_y)};
    add_lines(rows_with_line.size());
}

void GameImpl::generate_new_brick()
{
    cur_brick_ = next_bricks_.front();
    next_bricks_.pop_front();
    next_bricks_.emplace_back(bricks_bag_.get_next());
    ui_.refresh_next_bricks(next_bricks_);
}

void GameImpl::set_start_position_and_rotation()
{
    set_start_position();
    set_start_rotation();
    check_if_game_ended();
}

void GameImpl::add_score(unsigned long long amount)
{
    if (amount > 0)
    {
        score_ += amount;
        ui_.refresh_score(score_);
    }
}

void GameImpl::add_lines(int amount)
{
    if (amount > 0)
    {
        lines_count_ += amount;
        ui_.refresh_level_progress_bar(lines_count_);
        add_score_for_lines(amount);
        update_level();
    }
}

void GameImpl::update_level()
{
    if (lines_count_ >= next_level_lines_count_)
    {
        ++level_;
        lines_count_ -= next_level_lines_count_;
        ui_.refresh_level(level_);
        ui_.refresh_level_progress_bar(lines_count_);
        set_timeout_delay_(level_);
    }
}

void GameImpl::perform_action(const function<void()>& action)
{
    draw_bricks(false);
    action();
    draw_bricks();
    ui_.flush_matrix();
};

} // namespace Tetris
