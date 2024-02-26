#include "bag.h"
#include "board_impl.h"
#include "brick.h"
#include "brick_generator_impl.h"
#include "color.h"
#include "game_impl.h"
#include "game_state.h"
#include "game_ui.h"
#include "game_ui_mock.h"
#include "rng_mock.h"
#include "score_counter_impl.h"
#include "score_counter_mock.h"
#include "vector_2.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <vector>
#include <functional>

using std::function;
using std::find;
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
        return find(pixels.begin(), pixels.end(), pixel) != pixels.end();
    }
}

TEST(GameImpl, GameImpl)
{
    const Brick brick{{
        {{0, -1}},
        {{0, 0}},
        {{0, 1}},
        {{1, 1}}
    }};
    GameUIMock ui{};
    BoardImpl board{10, 20};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{Color::blue, Color::red}, rng}
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
    for_each_pixel_assert_true(board_pixels, [
        transformed_expected_cur_brick,
        transformed_expected_ghost_brick
    ](Pixel pixel)-> bool{
        return pixel.empty() != is_in(pixel, transformed_expected_cur_brick.pixels)
            or is_in(pixel, transformed_expected_ghost_brick.pixels);
    });
}

TEST(GameImpl, move_down_free_fall)
{
    const Brick brick{{
        {{0, -1}},
        {{0, 0}},
        {{0, 1}},
        {{1, 1}}
    }};
    GameUIMock ui{};
    BoardImpl board{10, 20};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{Color::blue}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
    const Vector2 expected_cur_brick_position{4, 2};
    const Vector2 expected_ghost_brick_position{4, 18};
    game.tick();
    const Brick transformed_cur_brick{game.get_transformed_cur_brick()};
    const Brick transformed_ghost_brick{game.get_transformed_ghost_brick()};
    vector<vector<Pixel>> board_pixels{game.get_board_pixels()};
    
    ASSERT_TRUE(game.get_cur_brick_position() == expected_cur_brick_position);
    ASSERT_TRUE(game.get_ghost_brick_position() == expected_ghost_brick_position);
    for_each_pixel_assert_true(board_pixels, [
        transformed_cur_brick,
        transformed_ghost_brick
    ](Pixel pixel)-> bool{
        return pixel.empty() != is_in(pixel, transformed_cur_brick.pixels)
            or is_in(pixel, transformed_ghost_brick.pixels);
    });
}

TEST(GameImpl, move_down_place)
{
    const Brick brick{{
        {{0, -1}},
        {{0, 0}},
        {{0, 1}},
        {{1, 1}}
    }};
    GameUIMock ui{};
    BoardImpl board{10, 20};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{Color::blue, Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
    const Vector2 expected_cur_brick_position{4, 1};
    const Vector2 expected_ghost_brick_position{4, 15};
    const Brick transformed_expected_placed_brick{Brick::get_translated(game.get_cur_brick(), {4, 18})};
    for(int i{0}; i < 18; ++i)
        game.tick();
    const Brick transformed_cur_brick{game.get_transformed_cur_brick()};
    const Brick transformed_ghost_brick{game.get_transformed_ghost_brick()};
    vector<vector<Pixel>> board_pixels{game.get_board_pixels()};
    
    ASSERT_TRUE(game.get_state() == GameState::paused);
    ASSERT_EQ(game.get_score(), 0);
    ASSERT_EQ(game.get_tetrises(), 0);
    ASSERT_TRUE(game.get_cur_brick_position() == expected_cur_brick_position);
    ASSERT_TRUE(game.get_ghost_brick_position() == expected_ghost_brick_position);
    for_each_pixel_assert_true(board_pixels, [
        transformed_cur_brick,
        transformed_ghost_brick,
        transformed_expected_placed_brick
    ](Pixel pixel)-> bool{
        return pixel.empty() != is_in(pixel, transformed_cur_brick.pixels)
            or is_in(pixel, transformed_ghost_brick.pixels)
            or is_in(pixel, transformed_expected_placed_brick.pixels);
    });
}

TEST(GameImpl, move_down_remove_lines_without_tetris)
{
    const Brick base_brick{{ {{-1, 0}}, {{1, 0}} }};
    const Brick falling_brick{{ {{0, 0}}, {{0, 1}} }};
    const Color bricks_color{Color::blue};
    const Brick expected_remaining_brick{{ {{1, 9}, bricks_color} }};
    GameUIMock ui{};
    BoardImpl board{3, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{base_brick, falling_brick}, rng},
        Bag<Color>{{bricks_color}, rng}
    };
    ScoreCounterImpl score_counter{10, 5, 3};
    GameImpl game{ui, board, brick_generator, score_counter};
    for(int i{0}; i < 20; ++i)
        game.tick();
    const Brick transformed_cur_brick{game.get_transformed_cur_brick()};
    const Brick transformed_ghost_brick{game.get_transformed_ghost_brick()};
    vector<vector<Pixel>> board_pixels{game.get_board_pixels()};
    
    ASSERT_EQ(game.get_score(), 10);
    ASSERT_EQ(game.get_tetrises(), 0);
    for_each_pixel_assert_true(board_pixels, [
        transformed_cur_brick,
        transformed_ghost_brick,
        expected_remaining_brick
    ](Pixel pixel)-> bool{
        return pixel.empty() != is_in(pixel, transformed_cur_brick.pixels)
            or is_in(pixel, transformed_ghost_brick.pixels)
            or is_in(pixel, expected_remaining_brick.pixels);
    });
}

TEST(GameImpl, move_down_remove_lines_with_tetris)
{
    const Brick base_brick{{
        {{-1, 0}},
        {{1, 0}},
        {{-1, 1}},
        {{1, 1}},
        {{-1, 2}},
        {{1, 2}},
        {{-1, 3}},
        {{1, 3}},
    }};
    const Brick falling_brick{{
        {{0, 0}},
        {{0, 1}},
        {{0, 2}},
        {{0, 3}},
        {{0, 4}},
    }};
    const Color bricks_color{Color::blue};
    const Brick expected_remaining_brick{{ {{1, 9}, bricks_color} }};
    GameUIMock ui{};
    BoardImpl board{3, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{base_brick, falling_brick}, rng},
        Bag<Color>{{bricks_color}, rng}
    };
    ScoreCounterImpl score_counter{10, 0, 0};
    GameImpl game{ui, board, brick_generator, score_counter};
    for(int i{0}; i < 13; ++i)
        game.tick();
    const Brick transformed_cur_brick{game.get_transformed_cur_brick()};
    const Brick transformed_ghost_brick{game.get_transformed_ghost_brick()};
    vector<vector<Pixel>> board_pixels{game.get_board_pixels()};
    
    ASSERT_EQ(game.get_score(), 40);
    ASSERT_EQ(game.get_tetrises(), 1);
    for_each_pixel_assert_true(board_pixels, [
        transformed_cur_brick,
        transformed_ghost_brick,
        expected_remaining_brick
    ](Pixel pixel)-> bool{
        return pixel.empty() != is_in(pixel, transformed_cur_brick.pixels)
            or is_in(pixel, transformed_ghost_brick.pixels)
            or is_in(pixel, expected_remaining_brick.pixels);
    });
}

TEST(GameImpl, move_down_end_game)
{
    const Brick brick{{ {{0, -1}}, {{0, 0}}, {{0, 1}} }};
    GameUIMock ui{};
    BoardImpl board{5, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
    for(int i{0}; i < 15; ++i)
        game.tick();

    ASSERT_TRUE(game.get_state() == GameState::ended);
}

TEST(GameImpl, move_left)
{
    const Brick brick{{ {{-1, 0}}, {{0, 0}}, {{1, 0}} }};
    GameUIMock ui{};
    BoardImpl board{5, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.move_left();
   
    ASSERT_TRUE(game.get_cur_brick_position() == (Vector2{1, 0}));
}

TEST(GameImpl, move_left_blocked)
{
    const Brick brick{{ {{-1, 0}}, {{0, 0}}, {{1, 0}} }};
    GameUIMock ui{};
    BoardImpl board{3, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.move_left();
    
    ASSERT_TRUE(game.get_cur_brick_position() == (Vector2{1, 0}));
}

TEST(GameImpl, move_right)
{
    const Brick brick{{ {{-1, 0}}, {{0, 0}}, {{1, 0}} }};
    GameUIMock ui{};
    BoardImpl board{5, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.move_right();
    
    ASSERT_TRUE(game.get_cur_brick_position() == (Vector2{3, 0}));
}

TEST(GameImpl, move_right_blocked)
{
    const Brick brick{{ {{-1, 0}}, {{0, 0}}, {{1, 0}} }};
    GameUIMock ui{};
    BoardImpl board{3, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.move_right();
    
    ASSERT_TRUE(game.get_cur_brick_position() == (Vector2{1, 0}));
}

TEST(GameImpl, rotate)
{
    const Brick brick{{ {{-1, 0}}, {{0, 0}}, {{1, 0}} }};
    GameUIMock ui{};
    BoardImpl board{3, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.tick();
    game.rotate();
    
    ASSERT_EQ(game.get_cur_brick_rotation(), 1);
}


TEST(GameImpl, rotate_blocked)
{
    const Brick brick{{ {{-1, 0}}, {{0, 0}}, {{1, 0}} }};
    GameUIMock ui{};
    BoardImpl board{3, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{Color::red}, rng}
    };
    ScoreCounterMock score_counter{};
    GameImpl game{ui, board, brick_generator, score_counter};
        
    game.rotate();
    
    ASSERT_EQ(game.get_cur_brick_rotation(), 0);
}

TEST(GameImpl, hard_drop)
{
    const Color bricks_color{Color::blue};
    const Brick brick{{ {{-1, 0}}, {{0, 0}} }};
    const Brick expected_remaining_brick{{ {{0, 9}, bricks_color}, {{1, 9}, bricks_color} }};
    GameUIMock ui{};
    BoardImpl board{3, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{bricks_color}, rng}
    };
    ScoreCounterImpl score_counter{0, 0, 2};
    GameImpl game{ui, board, brick_generator, score_counter};

    game.hard_drop();
    const Brick transformed_cur_brick{game.get_transformed_cur_brick()};
    const Brick transformed_ghost_brick{game.get_transformed_ghost_brick()};
    vector<vector<Pixel>> board_pixels{game.get_board_pixels()};
    
    ASSERT_EQ(game.get_score(), 20);
    for_each_pixel_assert_true(board_pixels, [
        transformed_cur_brick,
        transformed_ghost_brick,
        expected_remaining_brick
    ](Pixel pixel)-> bool{
        return pixel.empty() != is_in(pixel, transformed_cur_brick.pixels)
            or is_in(pixel, transformed_ghost_brick.pixels)
            or is_in(pixel, expected_remaining_brick.pixels);
    });
}

TEST(GameImpl, soft_drop)
{
    const Color bricks_color{Color::blue};
    const Brick brick{{ {{-1, 0}}, {{0, 0}} }};
    const Brick expected_remaining_brick{{ {{0, 9}, bricks_color}, {{1, 9}, bricks_color} }};
    GameUIMock ui{};
    BoardImpl board{3, 10};
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{{brick}, rng},
        Bag<Color>{{bricks_color}, rng}
    };
    ScoreCounterImpl score_counter{0, 1, 0};
    GameImpl game{ui, board, brick_generator, score_counter};

    game.soft_drop();
    ASSERT_EQ(game.get_cur_brick_position().y, 1);
    ASSERT_EQ(game.get_score(), 1);
}