#include <algorithm>
#include <functional>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bag.h"
#include "board_impl.h"
#include "brick_generator_impl.h"
#include "brick.h"
#include "config.h"
#include "game_impl.h"
#include "game_state.h"
#include "game_ui_mock.h"
#include "rng_mock.h"
#include "score_counter_mock.h"
#include "vector_2.h"

using std::find;
using std::function;
using std::vector;
using testing::Eq;
using Tetris::Bag;
using Tetris::BoardImpl;
using Tetris::Brick;
using Tetris::BrickGeneratorImpl;
using Tetris::Cube;
using Tetris::GameConfig;
using Tetris::GameImpl;
using Tetris::GameState;
using Tetris::GameUiMock;
using Tetris::RngMock;
using Tetris::ScoreCounterMock;
using Tetris::Vector2;

namespace {
    using CubeMatrix = vector<vector<Cube>>;

    void for_each_cube_assert_true(
        const CubeMatrix& cubes,
        function<bool(Cube cube)> compare
    ){
        for (const auto& row : cubes)
        {
            for (const auto& cube : row)
                ASSERT_THAT(compare(cube), Eq(true));
        }
    }
    bool is_in(Cube cube, vector<Cube> cubes)
    {
        return find(cubes.begin(), cubes.end(), cube) != cubes.end();
    }
}

TEST(GameImpl, GameImpl)
{
    const Brick brick{{ {0, 0}, {0, 1}, {1, 1} }};
    GameUiMock ui{};
    BoardImpl board{10, 20};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{3, 1}, rng}
    };
    ScoreCounterMock score_counter{};
    GameConfig config{0, false};
    GameImpl game{
        ui,
        board,
        brick_generator,
        score_counter,
        config.brick_start_position_y,
        config.generate_ghost
    };
    const Brick expected_cur_brick{Brick::get_colored(brick, 3)};
    const Brick expected_next_brick{Brick::get_colored(brick, 1)};
    const Brick expected_hold_brick{};
    const Vector2 expected_cur_brick_position{4, 0};
    const int expected_cur_brick_rotation{0};
    const Brick transformed_expected_cur_brick{Brick::get_transformed(
        expected_cur_brick,
        expected_cur_brick_rotation,
        expected_cur_brick_position
    )};
    const CubeMatrix board_cubes{board.get_cubes()};

    ASSERT_THAT(game.get_state(), Eq(GameState::in_progress));
    ASSERT_THAT(game.get_score(), Eq(0));
    ASSERT_THAT(game.get_tetrises(), Eq(0));
    ASSERT_THAT(game.get_cur_brick(), Eq(expected_cur_brick));
    ASSERT_THAT(game.get_next_brick(), Eq(expected_next_brick));
    ASSERT_THAT(
        game.get_cur_brick_rotation(),
        Eq(expected_cur_brick_rotation)
    );
    ASSERT_THAT(
        game.get_cur_brick_position(),
        Eq(expected_cur_brick_position)
    );
    ASSERT_THAT(game.get_hold_brick(), Eq(expected_hold_brick));
    for_each_cube_assert_true(
        board_cubes,
        [transformed_expected_cur_brick](Cube cube){
            return cube.empty() != is_in(
                cube,
                transformed_expected_cur_brick.cubes);});
}