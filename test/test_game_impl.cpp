#include <algorithm>
#include <functional>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <boost/range/irange.hpp>

#include "bag.h"
#include "board_impl.h"
#include "brick_generator_impl.h"
#include "brick.h"
#include "color.h"
#include "game_impl.h"
#include "game_state.h"
#include "game_ui_mock.h"
#include "rng_mock.h"
#include "score_counter_impl.h"
#include "score_counter_mock.h"
#include "vector_2.h"

using boost::irange;
using std::find;
using std::function;
using std::vector;
using testing::Eq;
using Tetris::Bag;
using Tetris::BoardImpl;
using Tetris::Brick;
using Tetris::BrickGeneratorImpl;
using Tetris::Color;
using Tetris::GameImpl;
using Tetris::GameState;
using Tetris::GameUiMock;
using Tetris::Pixel;
using Tetris::RngMock;
using Tetris::ScoreCounterImpl;
using Tetris::ScoreCounterMock;
using Tetris::Vector2;

namespace {
    using Pixels = vector<vector<Pixel>>;

    void for_each_pixel_assert_true(
        const Pixels& pixels,
        function<bool(Pixel pixel)> compare
    ){
        for (const auto& row : pixels)
        {
            for (const auto& pixel : row)
                ASSERT_THAT(compare(pixel), Eq(true));
        }
    }
    bool is_in(Pixel pixel, vector<Pixel> pixels)
    {
        return find(pixels.begin(), pixels.end(), pixel) != pixels.end();
    }
}

TEST(GameImpl, GameImpl)
{
    const Brick brick{{
        {0, -1},
        {0, 0},
        {0, 1},
        {1, 1}
    }};
    GameUiMock ui{};
    BoardImpl board{10, 20};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{Color::blue, Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
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
    const Pixels board_pixels{game.get_board_pixels()};

    ASSERT_THAT(game.get_state(), Eq(GameState::in_progress));
    ASSERT_THAT(game.get_score(), Eq(0));
    ASSERT_THAT(game.get_tetrises(), Eq(0));
    ASSERT_THAT(game.get_cur_brick(), Eq(expected_cur_brick));
    ASSERT_THAT(game.get_next_brick(), Eq(expected_next_brick));
    ASSERT_THAT(game.get_cur_brick_rotation(), Eq(expected_cur_brick_rotation));
    ASSERT_THAT(game.get_cur_brick_position(), Eq(expected_cur_brick_position));
    ASSERT_THAT(game.get_ghost_brick(), Eq(expected_ghost_brick));
    ASSERT_THAT(game.get_ghost_brick_position(), Eq(expected_ghost_brick_position));
    ASSERT_THAT(game.get_hold_brick(), Eq(expected_hold_brick));
    for_each_pixel_assert_true(board_pixels, [
        transformed_expected_cur_brick,
        transformed_expected_ghost_brick
    ](Pixel pixel){
        return pixel.empty() != is_in(pixel, transformed_expected_cur_brick.pixels)
            or is_in(pixel, transformed_expected_ghost_brick.pixels);
    });
}

TEST(GameImpl, move_down_free_fall)
{
    const Brick brick{{ {0, -1}, {0, 0}, {0, 1}, {1, 1} }};
    GameUiMock ui{};
    BoardImpl board{10, 20};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{Color::blue}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
    const Vector2 expected_cur_brick_position{4, 2};
    const Vector2 expected_ghost_brick_position{4, 18};
    game.handle_timeout();
    const Brick transformed_cur_brick{game.get_transformed_cur_brick()};
    const Brick transformed_ghost_brick{game.get_transformed_ghost_brick()};
    const Pixels board_pixels{game.get_board_pixels()};
    
    ASSERT_THAT(game.get_cur_brick_position(), Eq(expected_cur_brick_position));
    ASSERT_THAT(game.get_ghost_brick_position(), Eq(expected_ghost_brick_position));
    for_each_pixel_assert_true(board_pixels, [
        transformed_cur_brick,
        transformed_ghost_brick
    ](Pixel pixel){
        return pixel.empty() != is_in(pixel, transformed_cur_brick.pixels)
            or is_in(pixel, transformed_ghost_brick.pixels);
    });
}

TEST(GameImpl, move_down_place)
{
    const Brick brick{{ {0, -1}, {0, 0}, {0, 1}, {1, 1} }};
    GameUiMock ui{};
    BoardImpl board{10, 20};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{Color::blue, Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
    const Vector2 expected_cur_brick_position{4, 1};
    const Vector2 expected_ghost_brick_position{4, 15};
    const Brick transformed_expected_placed_brick{Brick::get_translated(game.get_cur_brick(), {4, 18})};
    for (const auto& i : irange(18))
        game.handle_timeout();
    const Brick transformed_cur_brick{game.get_transformed_cur_brick()};
    const Brick transformed_ghost_brick{game.get_transformed_ghost_brick()};
    const Pixels board_pixels{game.get_board_pixels()};
    
    ASSERT_THAT(game.get_cur_brick_position(), Eq(expected_cur_brick_position));
    ASSERT_THAT(game.get_ghost_brick_position(), Eq(expected_ghost_brick_position));
    for_each_pixel_assert_true(board_pixels, [
        transformed_cur_brick,
        transformed_ghost_brick,
        transformed_expected_placed_brick
    ](Pixel pixel){
        return pixel.empty() != is_in(pixel, transformed_cur_brick.pixels)
            or is_in(pixel, transformed_ghost_brick.pixels)
            or is_in(pixel, transformed_expected_placed_brick.pixels);
    });
}

TEST(GameImpl, move_down_remove_lines_without_tetris)
{
    const Brick base_brick{{ {-1, 0}, {1, 0} }};
    const Brick falling_brick{{ {0, 0}, {0, 1} }};
    const Color bricks_color{Color::blue};
    const Brick expected_remaining_brick{{ {1, 9, bricks_color} }};
    GameUiMock ui{};
    BoardImpl board{3, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{base_brick, falling_brick}, rng},
        Bag{{bricks_color}, rng}
    };
    ScoreCounterImpl score_counter{10, 5, 3};
    GameImpl game{ui, board, brick_generator, score_counter};
    for (const auto& i : irange(20))
        game.handle_timeout();
    const Brick transformed_cur_brick{game.get_transformed_cur_brick()};
    const Brick transformed_ghost_brick{game.get_transformed_ghost_brick()};
    const Pixels board_pixels{game.get_board_pixels()};
    
    ASSERT_THAT(game.get_score(), Eq(10));
    ASSERT_THAT(game.get_tetrises(), Eq(0));
    for_each_pixel_assert_true(board_pixels, [
        transformed_cur_brick,
        transformed_ghost_brick,
        expected_remaining_brick
    ](Pixel pixel){
        return pixel.empty() != is_in(pixel, transformed_cur_brick.pixels)
            or is_in(pixel, transformed_ghost_brick.pixels)
            or is_in(pixel, expected_remaining_brick.pixels);
    });
}

TEST(GameImpl, move_down_remove_lines_with_tetris)
{
    const Brick base_brick{{
        {-1, 0}, {1, 0},
        {-1, 1}, {1, 1},
        {-1, 2}, {1, 2},
        {-1, 3}, {1, 3},
    }};
    const Brick falling_brick{{ {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4} }};
    const Color bricks_color{Color::blue};
    const Brick expected_remaining_brick{{ {1, 9, bricks_color} }};
    GameUiMock ui{};
    BoardImpl board{3, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{base_brick, falling_brick}, rng},
        Bag{{bricks_color}, rng}
    };
    ScoreCounterImpl score_counter{10, 0, 0};
    GameImpl game{ui, board, brick_generator, score_counter};
    for (const auto& i : irange(13))
        game.handle_timeout();
    const Brick transformed_cur_brick{game.get_transformed_cur_brick()};
    const Brick transformed_ghost_brick{game.get_transformed_ghost_brick()};
    const Pixels board_pixels{game.get_board_pixels()};
    
    ASSERT_THAT(game.get_score(), Eq(40));
    ASSERT_THAT(game.get_tetrises(), Eq(1));
    for_each_pixel_assert_true(board_pixels, [
        transformed_cur_brick,
        transformed_ghost_brick,
        expected_remaining_brick
    ](Pixel pixel){
        return pixel.empty() != is_in(pixel, transformed_cur_brick.pixels)
            or is_in(pixel, transformed_ghost_brick.pixels)
            or is_in(pixel, expected_remaining_brick.pixels);
    });
}

TEST(GameImpl, move_down_end_game)
{
    const Brick brick{{ {0, -1}, {0, 0}, {0, 1} }};
    GameUiMock ui{};
    BoardImpl board{5, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
    for (const auto& i : irange(15))
        game.handle_timeout();

    ASSERT_THAT(game.get_state(), Eq(GameState::ended));
}

TEST(GameImpl, handle_move_left)
{
    const Brick brick{{ {-1, 0}, {0, 0}, {1, 0} }};
    GameUiMock ui{};
    BoardImpl board{5, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.handle_move_left();
   
    ASSERT_THAT(game.get_cur_brick_position(), Eq(Vector2{1, 0}));
}

TEST(GameImpl, move_left_blocked)
{
    const Brick brick{{ {-1, 0}, {0, 0}, {1, 0} }};
    GameUiMock ui{};
    BoardImpl board{3, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.handle_move_left();
    
    ASSERT_THAT(game.get_cur_brick_position(), Eq(Vector2{1, 0}));
}

TEST(GameImpl, handle_move_right)
{
    const Brick brick{{ {-1, 0}, {0, 0}, {1, 0} }};
    GameUiMock ui{};
    BoardImpl board{5, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.handle_move_right();
    
    ASSERT_THAT(game.get_cur_brick_position(), Eq(Vector2{3, 0}));
}

TEST(GameImpl, move_right_blocked)
{
    const Brick brick{{ {-1, 0}, {0, 0}, {1, 0} }};
    GameUiMock ui{};
    BoardImpl board{3, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.handle_move_right();
    
    ASSERT_THAT(game.get_cur_brick_position(), Eq(Vector2{1, 0}));
}

TEST(GameImpl, handle_rotate)
{
    const Brick brick{{ {-1, 0}, {0, 0}, {1, 0} }};
    GameUiMock ui{};
    BoardImpl board{3, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.handle_timeout();
    game.handle_rotate();
    
    ASSERT_THAT(game.get_cur_brick_rotation(), Eq(1));
}


TEST(GameImpl, rotate_blocked)
{
    const Brick brick{{ {-1, 0}, {0, 0}, {1, 0} }};
    GameUiMock ui{};
    BoardImpl board{3, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.handle_rotate();
    
    ASSERT_THAT(game.get_cur_brick_rotation(), Eq(0));
}

TEST(GameImpl, handle_hard_drop)
{
    const Color bricks_color{Color::blue};
    const Brick brick{{ {-1, 0}, {0, 0} }};
    const Brick expected_remaining_brick{{
        {0, 9, bricks_color},
        {1, 9, bricks_color},
    }};
    GameUiMock ui{};
    BoardImpl board{3, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{bricks_color}, rng}
    };
    ScoreCounterImpl score_counter{0, 0, 2};
    GameImpl game{ui, board, brick_generator, score_counter};

    game.handle_hard_drop();
    const Brick transformed_cur_brick{game.get_transformed_cur_brick()};
    const Brick transformed_ghost_brick{game.get_transformed_ghost_brick()};
    const Pixels board_pixels{game.get_board_pixels()};
    
    ASSERT_THAT(game.get_score(), Eq(20));
    for_each_pixel_assert_true(board_pixels, [
        transformed_cur_brick,
        transformed_ghost_brick,
        expected_remaining_brick
    ](Pixel pixel){
        return pixel.empty() != is_in(pixel, transformed_cur_brick.pixels)
            or is_in(pixel, transformed_ghost_brick.pixels)
            or is_in(pixel, expected_remaining_brick.pixels);
    });
}

TEST(GameImpl, handle_soft_drop)
{
    const Color bricks_color{Color::blue};
    const Brick brick{{ {-1, 0}, {0, 0} }};
    const Brick expected_remaining_brick{{
        {0, 9, bricks_color},
        {1, 9, bricks_color},
    }};
    GameUiMock ui{};
    BoardImpl board{3, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick}, rng},
        Bag{{bricks_color}, rng}
    };
    ScoreCounterImpl score_counter{0, 1, 0};
    GameImpl game{ui, board, brick_generator, score_counter};

    game.handle_soft_drop();
    ASSERT_THAT(game.get_cur_brick_position().y, Eq(1));
    ASSERT_THAT(game.get_score(), Eq(1));
}

TEST(GameImpl, hold_locking)
{
    const Color bricks_color{Color::red};
    const Brick brick{{ {-1, 0, bricks_color}, {0, 0, bricks_color} }};
    const Brick expected_remaining_brick{{
        {0, 0, bricks_color},
        {0, 1, bricks_color},
    }};
    GameUiMock ui{};
    BoardImpl board{3, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick, expected_remaining_brick}, rng},
        Bag{{bricks_color}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};

    for (const auto& i : irange(5))
        game.handle_timeout();

    for (const auto& i : irange(2))
    {
        game.handle_hold();
        ASSERT_THAT(game.get_hold_brick(), Eq(brick));
        ASSERT_THAT(game.get_cur_brick(), Eq(expected_remaining_brick));
        ASSERT_THAT(game.get_cur_brick_position(), Eq(Vector2{1, 0}));
    }
}

TEST(GameImpl, hold_unlocked)
{
    const Color bricks_color{Color::red};
    const Brick brick1{{ {-1, 0, bricks_color}, {0, 0, bricks_color} }};
    const Brick brick2{{ {0, 0, bricks_color}, {1, 0, bricks_color} }};
    const Brick brick3{{ {0, 0, bricks_color}, {0, 1, bricks_color} }};
    GameUiMock ui{};
    BoardImpl board{3, 10};
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{{brick1, brick2, brick3}, rng},
        Bag{{bricks_color}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};

    
    game.handle_hold();
    ASSERT_THAT(game.get_hold_brick(), Eq(brick1));
    ASSERT_THAT(game.get_cur_brick(), Eq(brick2));

    game.handle_hard_drop();
    game.handle_hold();

    ASSERT_THAT(game.get_hold_brick(), Eq(brick3));
    ASSERT_THAT(game.get_cur_brick(), Eq(brick1));
}