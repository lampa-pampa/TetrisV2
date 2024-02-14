#include "board_impl.h"
#include "brick.h"
#include "color.h"
#include "pixel.h"
#include <algorithm>
#include <gtest/gtest.h>
#include <vector>

using std::vector;
using std::find;

TEST(BoardImpl, BoardImpl)
{
    int width = 10;
    int height = 20;
    BoardImpl board{width, height};
    vector<vector<Pixel>> pixels = board.get_pixels();
    for(int y{0}; y < height; ++y)
    {
        for(int x{0}; x < width; ++x)
        {
            Pixel expected_pixel{{x, y}};
            ASSERT_TRUE(pixels[y][x] == expected_pixel);
        }
    }
}

TEST(BoardImpl, test_get_width)
{
    BoardImpl board{10, 20};
    ASSERT_EQ(board.get_width(), 10);
}

TEST(BoardImpl, test_is_space_for_brick)
{
    int width = 3;
    int height = 3;
    BoardImpl board{3, 3};
    const Brick brick1{{ {{0, 0}} }};
    ASSERT_TRUE(board.is_space_for_brick(brick1));
    
    const Brick brick2{{ {{1, 3}} }};
    ASSERT_FALSE(board.is_space_for_brick(brick2));

    Brick full_brick{{}};
    for(int y{0}; y < height; ++y)
    {
        for(int x{0}; x < width; ++x)
            full_brick.pixels.emplace_back(Pixel{{x, y}, Color::red});
    }
    board.add_brick(full_brick);
    ASSERT_FALSE(board.is_space_for_brick(brick1));
}

TEST(BoardImpl, test_add_brick)
{
    int width = 3;
    int height = 3;
    BoardImpl board{width, height};
    const Brick brick{{ {{1, 2}, Color::green}, {{2, 2}, Color::green} }};
    board.add_brick(brick);
    vector<vector<Pixel>> pixels = board.get_pixels();
    for(int y{0}; y < height; ++y)
    {
        for(int x{0}; x < width; ++x)
        {
            bool is_in_brick = (find(brick.pixels.begin(), brick.pixels.end(), pixels[y][x]) != brick.pixels.end());
            ASSERT_TRUE(pixels[y][x].empty() == not is_in_brick);
        }
    }
}

TEST(BoardImpl, remove_brick)
{
    int width = 3;
    int height = 3;
    BoardImpl board{width, height};
    const Brick brick{{ {{0, 0}}, {{0, 1}} }};
    Brick full_brick{{}};
    for(int y{0}; y < height; ++y)
    {
        for(int x{0}; x < width; ++x)
            full_brick.pixels.emplace_back(Pixel{{x, y}, Color::red});
    }
    board.add_brick(full_brick);
    board.remove_brick(brick);
    vector<vector<Pixel>> pixels = board.get_pixels();
    for(int y{0}; y < height; ++y)
    {
        for(int x{0}; x < width; ++x)
        {
            bool is_in_brick = (find(brick.pixels.begin(), brick.pixels.end(), pixels[y][x]) != brick.pixels.end());
            ASSERT_TRUE(pixels[y][x].empty() == is_in_brick);
        }
    }
}