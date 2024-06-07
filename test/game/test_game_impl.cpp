#include "game/game_impl.h"

#include <tuple>
#include <utility>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "board/board_impl.h"
#include "brick/brick.h"
#include "brick/brick_generator_impl.h"
#include "config/config.h"
#include "game/game_state.h"
#include "rng/rng_mock.h"
#include "score_counter/score_counter_impl.h"
#include "ui/color/color_id_name.h"
#include "ui/game_ui/game_ui_mock.h"
#include "vector_2/vector_2.h"

using boost::irange;
using std::pair;
using std::tuple;
using std::vector;
using testing::Eq;
using Tetris::BoardImpl;
using Tetris::Brick;
using Tetris::BrickGeneratorImpl;
using Tetris::GameConfig;
using Tetris::GameImpl;
using Tetris::GameState;
using Tetris::RngMock;
using Tetris::ScoreCounterImpl;
using Tetris::Settings;
using Tetris::Vector2;
using Tetris::Ui::ColorIdName;
using Tetris::Ui::GameUiMock;

namespace
{
struct GameImplTest
{
    GameImplTest(GameConfig config)
      : ui{},
        board{
            config.board.size,
            config.board.offset,
        },
        rng{},
        brick_generator{
            {config.bricks, rng},
            {config.color_id_names, rng},
        },
        score_counter{
            config.score_counter.score_for,
        },
        game{
            ui,
            board,
            brick_generator,
            score_counter,
            config.default_settings,
            config.brick_spawn_position,
            config.next_level_lines_count,
        }
    {}
    GameUiMock ui;
    BoardImpl board;
    RngMock rng;
    BrickGeneratorImpl brick_generator;
    ScoreCounterImpl score_counter;
    GameImpl game;
};
} // namespace

TEST(GameImpl, GameImpl)
{
    const vector<pair<GameConfig,
        tuple<GameState,
            unsigned long long,
            unsigned long long,
            Brick,
            Vector2,
            int,
            Brick,
            Brick,
            bool,
            Settings>>>
        config_to_expected{
            {
                {
                    {{5, 10}},
                    {{1, 2, 4}},
                    {{{{0, 0}, {0, 1}}}},
                    {ColorIdName::white},
                    {0, false},
                    {2, 5},
                    10,
                },
                {
                    GameState::in_progress,
                    0,
                    0,
                    {{
                        {0, 0, ColorIdName::white},
                        {0, 1, ColorIdName::white},
                    }},
                    {2, 5},
                    0,
                    {{
                        {0, 0, ColorIdName::white},
                        {0, 1, ColorIdName::white},
                    }},
                    {{}},
                    true,
                    {0, false},
                },
            },
            {
                {
                    {{3, 5}, 2},
                    {{3, 12, 24}},
                    {{{{0, 0}, {1, 2}}}, {{{0, 0}, {1, 3}}}},
                    {ColorIdName::dark_gray, ColorIdName::white},
                    {0, false},
                    {1, 2},
                    10,
                },
                {
                    GameState::in_progress,
                    0,
                    0,
                    {{
                        {0, 0, ColorIdName::dark_gray},
                        {1, 2, ColorIdName::dark_gray},
                    }},
                    {1, 2},
                    0,
                    {{
                        {0, 0, ColorIdName::white},
                        {1, 3, ColorIdName::white},
                    }},
                    {{}},
                    true,
                    {0, false},
                },
            },
            {
                {
                    {{10, 20}, 2},
                    {{0, 0, 0}},
                    {{{{0, 0}, {1, 0}}}, {{{-1, 0}, {0, 0}}}},
                    {ColorIdName::white},
                    {0, false},
                    {4, 3},
                    10,
                },
                {
                    GameState::in_progress,
                    0,
                    0,
                    {{
                        {0, 0, ColorIdName::white},
                        {1, 0, ColorIdName::white},
                    }},
                    {4, 3},
                    0,
                    {{
                        {-1, 0, ColorIdName::white},
                        {0, 0, ColorIdName::white},
                    }},
                    {{}},
                    true,
                    {0, false},
                },
            },
        };

    for (const auto& pair : config_to_expected)
    {
        const auto& [state,
            score,
            tetrises,
            cur_brick,
            cur_brick_position,
            cur_brick_rotation,
            next_brick,
            hold_brick,
            can_hold,
            settings]{pair.second};

        GameImplTest game_test{pair.first};
        const GameImpl& game{game_test.game};

        ASSERT_THAT(game.get_state(), Eq(state));
        ASSERT_THAT(game.get_score(), Eq(score));
        ASSERT_THAT(game.get_tetrises(), Eq(tetrises));
        ASSERT_THAT(game.get_cur_brick(), Eq(cur_brick));
        ASSERT_THAT(game.get_cur_brick_position(), Eq(cur_brick_position));
        ASSERT_THAT(game.get_cur_brick_rotation(), Eq(cur_brick_rotation));
        ASSERT_THAT(game.get_next_bricks()[0], Eq(next_brick));
        ASSERT_THAT(game.get_hold_brick(), Eq(hold_brick));
        ASSERT_THAT(game.get_can_hold(), Eq(can_hold));
        ASSERT_THAT(game.get_settings(), Eq(settings));
    }
}
TEST(GameImpl, handle_soft_drop)
{
    const GameConfig initial_config{
        {{3}, 0},
        {{1, 3, 2}},
        {{{{0, 0}}}},
        {
            ColorIdName::white,
            ColorIdName::davy_s_grey,
            ColorIdName::dodie_yellow,
        },
        {0, false},
        {1, 0},
    };
    const vector<pair<int, tuple<GameState, int, Brick, Vector2, Brick>>>
        soft_drops_to_expected{
            {1,
                {
                    GameState::in_progress,
                    2,
                    {{{0, 0, ColorIdName::white}}},
                    {1, 1},
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                }},
            {4,
                {
                    GameState::in_progress,
                    8,
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                    {1, 1},
                    {{{0, 0, ColorIdName::dodie_yellow}}},
                }},
            {6,
                {
                    GameState::ended,
                    12,
                    {{{0, 0, ColorIdName::white}}},
                    {1, 0},
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                }},
        };

    for (const auto& pair : soft_drops_to_expected)
    {
        const auto& [state, score, cur_brick, cur_brick_position, next_brick]{
            pair.second};

        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(pair.first))
            game.handle_soft_drop();

        ASSERT_THAT(game.get_state(), Eq(state));
        ASSERT_THAT(game.get_score(), Eq(score));
        ASSERT_THAT(game.get_cur_brick(), Eq(cur_brick));
        ASSERT_THAT(game.get_cur_brick_position(), Eq(cur_brick_position));
        ASSERT_THAT(game.get_next_bricks()[0], Eq(next_brick));
    }
}

TEST(GameImpl, handle_timeout)
{
    const GameConfig initial_config{
        {{3}, 0},
        {{1, 3, 2}},
        {{{{0, 0}}}},
        {
            ColorIdName::white,
            ColorIdName::davy_s_grey,
            ColorIdName::dodie_yellow,
        },
        {0, false},
        {1, 0},
    };
    const vector<pair<int, tuple<GameState, int, Brick, Vector2, Brick>>>
        soft_drops_to_expected{
            {1,
                {
                    GameState::in_progress,
                    2,
                    {{{0, 0, ColorIdName::white}}},
                    {1, 1},
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                }},
            {4,
                {
                    GameState::in_progress,
                    8,
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                    {1, 1},
                    {{{0, 0, ColorIdName::dodie_yellow}}},
                }},
            {6,
                {
                    GameState::ended,
                    12,
                    {{{0, 0, ColorIdName::white}}},
                    {1, 0},
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                }},
        };

    for (const auto& pair : soft_drops_to_expected)
    {
        const auto& [state, score, cur_brick, cur_brick_position, next_brick]{
            pair.second};

        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(pair.first))
            game.handle_soft_drop();

        ASSERT_THAT(game.get_state(), Eq(state));
        ASSERT_THAT(game.get_score(), Eq(score));
        ASSERT_THAT(game.get_cur_brick(), Eq(cur_brick));
        ASSERT_THAT(game.get_cur_brick_position(), Eq(cur_brick_position));
        ASSERT_THAT(game.get_next_bricks()[0], Eq(next_brick));
    }
}

TEST(GameImpl, handle_move_left)
{
    const GameConfig initial_config{
        {{5, 3}, 0},
        {{0, 0, 0}},
        {{{{0, 0}}}},
        {ColorIdName::white},
        {0, false},
        {2, 0},
    };
    const vector<pair<int, Vector2>> moves_left_to_expected{
        {1, {1, 0}},
        {2, {0, 0}},
        {3, {0, 0}},
    };

    for (const auto& pair : moves_left_to_expected)
    {
        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(pair.first))
            game.handle_move_left();

        ASSERT_THAT(game.get_cur_brick_position(), Eq(pair.second));
    }
}

TEST(GameImpl, handle_move_right)
{
    const GameConfig initial_config{
        {{5, 3}, 0},
        {{0, 0, 0}},
        {{{{0, 0}}}},
        {ColorIdName::white},
        {0, false},
        {2, 0},
    };
    const vector<pair<int, Vector2>> moves_right_to_expected{
        {1, {3, 0}},
        {2, {4, 0}},
        {3, {4, 0}},
    };

    for (const auto& pair : moves_right_to_expected)
    {
        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(pair.first))
            game.handle_move_right();

        ASSERT_THAT(game.get_cur_brick_position(), Eq(pair.second));
    }
}

TEST(GameImpl, handle_rotate_clockwise)
{
    const GameConfig initial_config{
        {{3}, 0},
        {{0, 0, 0}},
        {{{{0, 0}, {1, 0}}}},
        {ColorIdName::white},
        {0, false},
        {1, 0},
    };
    const vector<pair<tuple<int, int, int>, int>>
        timeouts_moves_left_and_rotations_to_expected{
            {{1, 0, 3}, 3},
            {{0, 1, 2}, 1},
            {{2, 0, 3}, 0},
        };

    for (const auto& pair : timeouts_moves_left_and_rotations_to_expected)
    {
        const auto& [timeouts, moves_left, rotations]{pair.first};

        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(moves_left))
            game.handle_move_left();
        for (const auto& i : irange(timeouts))
            game.handle_timeout();
        for (const auto& i : irange(rotations))
            game.handle_rotate_clockwise();

        ASSERT_THAT(game.get_cur_brick_rotation(), Eq(pair.second));
    }
}

TEST(GameImpl, handle_rotate_counter_clockwise)
{
    const GameConfig initial_config{
        {{3}, 0},
        {{0, 0, 0}},
        {{{{-1, 0}, {0, 0}}}},
        {ColorIdName::white},
        {0, false},
        {1, 0},
    };
    const vector<pair<tuple<int, int, int>, int>>
        timeouts_moves_right_and_rotations_to_expected{
            {{1, 0, 3}, 1},
            {{0, 1, 2}, 3},
            {{2, 0, 3}, 0},
        };

    for (const auto& pair : timeouts_moves_right_and_rotations_to_expected)
    {
        const auto& [timeouts, moves_right, rotations]{pair.first};

        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(timeouts))
            game.handle_timeout();
        for (const auto& i : irange(moves_right))
            game.handle_move_right();
        for (const auto& i : irange(rotations))
            game.handle_rotate_counter_clockwise();

        ASSERT_THAT(game.get_cur_brick_rotation(), Eq(pair.second));
    }
}

TEST(GameImpl, handle_locking_hard_drop)
{
    const GameConfig initial_config{
        {{3}, 0},
        {{1, 3, 2}},
        {{{{0, 0}}}},
        {
            ColorIdName::white,
            ColorIdName::davy_s_grey,
            ColorIdName::dodie_yellow,
        },
        {0, false},
        {1, 0},
    };
    const vector<pair<int, tuple<GameState, int, Brick, Vector2, Brick>>>
        hard_drops_to_expected{
            {1,
                {
                    GameState::in_progress,
                    6,
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                    {1, 0},
                    {{{0, 0, ColorIdName::dodie_yellow}}},
                }},
            {2,
                {
                    GameState::in_progress,
                    9,
                    {{{0, 0, ColorIdName::dodie_yellow}}},
                    {1, 0},
                    {{{0, 0, ColorIdName::white}}},
                }},
            {3,
                {
                    GameState::ended,
                    9,
                    {{{0, 0, ColorIdName::white}}},
                    {1, 0},
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                }},
        };

    for (const auto& pair : hard_drops_to_expected)
    {
        const auto& [state, score, cur_brick, cur_brick_position, next_brick]{
            pair.second};

        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(pair.first))
            game.handle_locking_hard_drop();

        ASSERT_THAT(game.get_state(), Eq(state));
        ASSERT_THAT(game.get_score(), Eq(score));
        ASSERT_THAT(game.get_cur_brick(), Eq(cur_brick));
        ASSERT_THAT(game.get_cur_brick_position(), Eq(cur_brick_position));
        ASSERT_THAT(game.get_next_bricks()[0], Eq(next_brick));
    }
}

TEST(GameImpl, handle_no_locking_hard_drop)
{
    const GameConfig initial_config{
        {{3}, 0},
        {{1, 3, 2}},
        {{{{0, 0}}}},
        {
            ColorIdName::white,
            ColorIdName::davy_s_grey,
            ColorIdName::dodie_yellow,
        },
        {0, false},
        {1, 0},
    };
    const vector<pair<int, tuple<GameState, int, Brick, Vector2, Brick>>>
        hard_drops_to_expected{
            {1,
                {
                    GameState::in_progress,
                    6,
                    {{{0, 0, ColorIdName::white}}},
                    {1, 2},
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                }},
            {2,
                {
                    GameState::in_progress,
                    6,
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                    {1, 0},
                    {{{0, 0, ColorIdName::dodie_yellow}}},
                }},
            {5,
                {
                    GameState::ended,
                    9,
                    {{{0, 0, ColorIdName::white}}},
                    {1, 0},
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                }},
        };

    for (const auto& pair : hard_drops_to_expected)
    {
        const auto& [state, score, cur_brick, cur_brick_position, next_brick]{
            pair.second};

        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(pair.first))
            game.handle_no_locking_hard_drop();

        ASSERT_THAT(game.get_state(), Eq(state));
        ASSERT_THAT(game.get_score(), Eq(score));
        ASSERT_THAT(game.get_cur_brick(), Eq(cur_brick));
        ASSERT_THAT(game.get_cur_brick_position(), Eq(cur_brick_position));
        ASSERT_THAT(game.get_next_bricks()[0], Eq(next_brick));
    }
}

TEST(GameImpl, handle_hold)
{
    const GameConfig initial_config{
        {{3}, 0},
        {{0, 0, 0}},
        {{{{0, 0}}}},
        {
            ColorIdName::white,
            ColorIdName::davy_s_grey,
            ColorIdName::dodie_yellow,
        },
        {0, false},
        {1, 0},
    };
    const vector<
        pair<tuple<int, int>, tuple<Brick, Vector2, Brick, Brick, bool>>>
        timeouts_before_and_after_to_expected{
            {{0, 0},
                {
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                    {1, 0},
                    {{{0, 0, ColorIdName::dodie_yellow}}},
                    {{{0, 0, ColorIdName::white}}},
                    false,
                }},
            {{1, 2},
                {
                    {{{0, 0, ColorIdName::davy_s_grey}}},
                    {1, 2},
                    {{{0, 0, ColorIdName::dodie_yellow}}},
                    {{{0, 0, ColorIdName::white}}},
                    false,
                }},
            {{2, 3},
                {
                    {{{0, 0, ColorIdName::dodie_yellow}}},
                    {1, 0},
                    {{{0, 0, ColorIdName::white}}},
                    {{{0, 0, ColorIdName::white}}},
                    true,
                }},
        };

    for (const auto& pair : timeouts_before_and_after_to_expected)
    {
        const auto& [timeouts_before, timeouts_after]{pair.first};
        const auto& [cur_brick,
            cur_brick_position,
            next_brick,
            hold_brick,
            can_hold]{pair.second};

        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(timeouts_before))
            game.handle_timeout();
        for (const auto& i : irange(2))
            game.handle_hold();
        for (const auto& i : irange(timeouts_after))
            game.handle_timeout();

        ASSERT_THAT(game.get_cur_brick(), Eq(cur_brick));
        ASSERT_THAT(game.get_cur_brick_position(), Eq(cur_brick_position));
        ASSERT_THAT(game.get_next_bricks()[0], Eq(next_brick));
        ASSERT_THAT(game.get_hold_brick(), Eq(hold_brick));
        ASSERT_THAT(game.get_can_hold(), Eq(can_hold));
    }
}

TEST(GameImpl, update_level)
{
    const GameConfig initial_config{
        {{3}, 0},
        {{1, 2, 3}},
        {{{{-1, 0}, {0, 0}, {1, 0}}}},
        {ColorIdName::white},
        {1, false},
        {1, 2},
        10,
    };
    const vector<pair<int, int>> timeouts_to_expected{
        {1, 1},
        {10, 2},
        {25, 3},
    };

    for (const auto& pair : timeouts_to_expected)
    {
        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(pair.first))
            game.handle_timeout();

        ASSERT_THAT(game.get_level(), Eq(pair.second));
    }
}

TEST(GameImpl, set_start_position)
{
    const GameConfig initial_config{
        {{2, 5}, 2},
        {{0, 0, 0}},
        {{{{0, 0}, {0, 1}}}},
        {ColorIdName::white},
        {1, false},
        {0, 3},
    };
    const vector<pair<int, Vector2>> hard_drops_to_expected{
        {0, {0, 3}},
        {1, {0, 1}},
        {2, {0, -1}},
    };

    for (const auto& pair : hard_drops_to_expected)
    {
        GameImplTest game_test{initial_config};
        GameImpl& game{game_test.game};
        for (const auto& i : irange(pair.first))
            game.handle_locking_hard_drop();

        ASSERT_THAT(game.get_cur_brick_position(), Eq(pair.second));
    }
}
