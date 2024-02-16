#include "bag.h"
#include "board.h"
#include "board_impl.h"
#include "brick_generator.h"
#include "brick_generator_impl.h"
#include "color.h"
#include "game_impl.h"
#include "game_state.h"
#include "game_ui.h"
#include "game_ui_mock.h"
#include "rng_mock.h"
#include "vector_2.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <memory>
#include <functional>
#include <vector>

using std::unique_ptr;
using std::function;
using std::count;
using std::vector;

namespace {
    void for_each_pixel_assert_true(const vector<vector<Pixel>> &pixels, function<bool(Pixel pixel)> compare)
    {
        for(const vector<Pixel> &row : pixels)
        {
            for(const Pixel &pixel : row)
                ASSERT_TRUE(compare(pixel));
        }
    }
    bool is_in(Pixel pixel, vector<Pixel> pixels)
    {
        return count(pixels.begin(), pixels.end(), pixel) > 0;
    }
}

TEST(GameImpl, GameImpl)
{
    const Brick brick{{ {{0, -1}}, {{0, 0}}, {{0, 1}}, {{1, 1}} }};
    GameImpl game{
        std::unique_ptr<GameUI>{new GameUIMock{}},
        std::unique_ptr<Board>{new BoardImpl{10, 20}},
        std::unique_ptr<BrickGenerator>{new BrickGeneratorImpl{
            Bag<Brick>{{brick}, std::unique_ptr<RNG>{new RNGMock{}}},
            Bag<Color>{{Color::blue, Color::red}, std::unique_ptr<RNG>{new RNGMock{}}},
        }},
        nullptr,
    };
    const Brick expected_cur_brick{Brick::get_colored(brick, Color::blue)};
    const Brick expected_next_brick{Brick::get_colored(brick, Color::red)};
    const Brick expected_ghost_brick{Brick::get_ghostified(expected_cur_brick)};
    const Brick expected_hold_brick{};
    const Vector2 expected_cur_brick_position{4, 1};
    const int expected_cur_brick_rotation{0};
    const Vector2 expected_ghost_brick_position{4, 18};
    const Brick transformed_expected_cur_brick{Brick::get_transformed(
        expected_cur_brick,
        expected_cur_brick_rotation,
        expected_cur_brick_position
    )};
    const Brick transformed_expected_ghost_brick{Brick::get_transformed(
        expected_ghost_brick,
        expected_cur_brick_rotation,
        expected_ghost_brick_position
    )};
    vector<vector<Pixel>> board_pixels{game.get_board_pixels()};

    ASSERT_TRUE(game.get_state() == GameState::paused);
    ASSERT_EQ(game.get_score(), 0);
    ASSERT_EQ(game.get_tetrises(), 0);
    ASSERT_TRUE(game.get_cur_brick() == expected_cur_brick);
    ASSERT_TRUE(game.get_next_brick() == expected_next_brick);
    ASSERT_EQ(game.get_cur_brick_rotation(), expected_cur_brick_rotation);
    ASSERT_TRUE(game.get_cur_brick_position() == expected_cur_brick_position);
    ASSERT_TRUE(game.get_ghost_brick() == expected_ghost_brick);
    ASSERT_TRUE(game.get_ghost_brick_position() == expected_ghost_brick_position);
    ASSERT_TRUE(game.get_hold_brick() == expected_hold_brick);
    for_each_pixel_assert_true(board_pixels, [transformed_expected_cur_brick, transformed_expected_ghost_brick](Pixel pixel)-> bool{
        return pixel.empty() != is_in(pixel, transformed_expected_cur_brick.pixels)
            or is_in(pixel, transformed_expected_ghost_brick.pixels);
    });
}