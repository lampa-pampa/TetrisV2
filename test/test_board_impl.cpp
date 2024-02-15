#include "board_impl.h"
#include "brick.h"
#include "color.h"
#include "pixel.h"
#include "vector_2.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <vector>
#include <functional>

using std::vector;
using std::function;
using std::count;

namespace {
    Brick create_rectangle_brick(int width, int height, Color color)
    {
        Brick full_brick{};
        for(int y{0}; y < height; ++y)
        {
            for(int x{0}; x < width; ++x)
                full_brick.pixels.emplace_back(Pixel{{x, y}, color});
        }
        return full_brick;
    }
    void foreach_pixel(vector<vector<Pixel>> pixels, function<void(vector<vector<Pixel>> pixels, int x, int y)> func)
    {
        for(int y{0}; y < pixels.size(); ++y)
        {
            for(int x{0}; x < pixels[0].size(); ++x)
                func(pixels, x, y);
        }
    }
    bool is_in(Pixel pixel, vector<Pixel> pixels)
    {
        return count(pixels.begin(), pixels.end(), pixel) > 0;
    }
}

TEST(BoardImpl, BoardImpl)
{
    BoardImpl board{10, 20};
    vector<vector<Pixel>> pixels = board.get_pixels();
    
    foreach_pixel(pixels, [](vector<vector<Pixel>> pixels, int x, int y)-> void{
        ASSERT_TRUE(pixels[y][x].coords == (Vector2{x, y}));
    });
}

TEST(BoardImpl, is_space_for_brick_empty_board)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {{0, 0}} }};
    
    ASSERT_TRUE(board.is_space_for_brick(brick));
}

TEST(BoardImpl, is_space_for_brick_off_range)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {{1, 3}} }};
    
    ASSERT_FALSE(board.is_space_for_brick(brick));
}

TEST(BoardImpl, is_space_for_brick_filled_board)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {{0, 0}} }};
    board.add_brick(create_rectangle_brick(3, 3, Color::red));
    
    ASSERT_FALSE(board.is_space_for_brick(brick));    
}

TEST(BoardImpl, add_brick)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {{1, 2}, Color::green}, {{2, 2}, Color::green} }};
    board.add_brick(brick);
    vector<vector<Pixel>> pixels = board.get_pixels();
    
    foreach_pixel(pixels, [&brick](vector<vector<Pixel>> pixels, int x, int y)-> void{
        ASSERT_TRUE(pixels[y][x].empty() != is_in(pixels[y][x], brick.pixels));
    });
}

TEST(BoardImpl, remove_brick)
{
    BoardImpl board{3, 3};
    board.add_brick(create_rectangle_brick(3, 3, Color::red));
    const Brick brick{{ {{0, 0}}, {{0, 1}} }};   
    board.remove_brick(brick);
    vector<vector<Pixel>> pixels = board.get_pixels();
    
    foreach_pixel(pixels, [&brick](vector<vector<Pixel>> pixels, int x, int y)-> void{
        ASSERT_TRUE(pixels[y][x].empty() == is_in(pixels[y][x], brick.pixels));
    });
}

TEST(BoardImpl, remove_lines_in_range_and_compress_without_lines_in_range)
{
    BoardImpl board{3, 3};
    Brick brick = create_rectangle_brick(3, 2, Color::red);
    board.add_brick(brick);
    int lines = board.remove_lines_in_range_and_compress(2, 2);
    vector<vector<Pixel>> pixels = board.get_pixels();

    
    ASSERT_EQ(lines, 0);
    foreach_pixel(pixels, [&brick](vector<vector<Pixel>> pixels, int x, int y)-> void{
        ASSERT_TRUE(pixels[y][x].empty() != is_in(pixels[y][x], brick.pixels));
    });
}

TEST(BoardImpl, remove_lines_in_range_and_compress_with_lines_in_range)
{
    BoardImpl board{3, 3};
    board.add_brick(create_rectangle_brick(3, 2, Color::red));
    board.add_brick(create_rectangle_brick(2, 3, Color::red));
    const Brick brick{{ {{0, 2}, Color::red}, {{1, 2}, Color::red} }};
    int lines = board.remove_lines_in_range_and_compress(0, 2);
    vector<vector<Pixel>> pixels = board.get_pixels();
    
    ASSERT_EQ(lines, 2);
    foreach_pixel(pixels, [&brick](vector<vector<Pixel>> pixels, int x, int y)-> void{
        ASSERT_TRUE(pixels[y][x].empty() != is_in(pixels[y][x], brick.pixels));
    });
}