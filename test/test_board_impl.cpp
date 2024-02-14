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
using std::find;
using std::function;

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
}

TEST(BoardImpl, BoardImpl)
{
    BoardImpl board{10, 20};
    vector<vector<Pixel>> pixels = board.get_pixels();
    foreach_pixel(pixels, [](vector<vector<Pixel>> pixels, int x, int y)-> void{
        ASSERT_TRUE(pixels[y][x].coords == (Vector2{x, y}));
    });
}

TEST(BoardImpl, test_get_width)
{
    BoardImpl board{10, 20};
    ASSERT_EQ(board.get_width(), 10);
}

TEST(BoardImpl, test_is_space_for_brick)
{
    BoardImpl board{3, 3};
    const Brick brick1{{ {{0, 0}} }};
    ASSERT_TRUE(board.is_space_for_brick(brick1));
    
    const Brick brick2{{ {{1, 3}} }};
    ASSERT_FALSE(board.is_space_for_brick(brick2));

    board.add_brick(create_rectangle_brick(3, 3, Color::red));
    ASSERT_FALSE(board.is_space_for_brick(brick1));
}

TEST(BoardImpl, test_add_brick)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {{1, 2}, Color::green}, {{2, 2}, Color::green} }};
    board.add_brick(brick);
    vector<vector<Pixel>> pixels = board.get_pixels();
    foreach_pixel(pixels, [brick](vector<vector<Pixel>> pixels, int x, int y)-> void{
        bool is_in_brick = (find(brick.pixels.begin(), brick.pixels.end(), pixels[y][x]) != brick.pixels.end());
        ASSERT_TRUE(pixels[y][x].empty() == not is_in_brick);
    });
}

TEST(BoardImpl, remove_brick)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {{0, 0}}, {{0, 1}} }};   
    board.add_brick(create_rectangle_brick(3, 3, Color::red));
    board.remove_brick(brick);
    vector<vector<Pixel>> pixels = board.get_pixels();
    foreach_pixel(pixels, [brick](vector<vector<Pixel>> pixels, int x, int y)-> void{
        bool is_in_brick = (find(brick.pixels.begin(), brick.pixels.end(), pixels[y][x]) != brick.pixels.end());
        ASSERT_TRUE(pixels[y][x].empty() == is_in_brick);
    });
}

TEST(BoardImpl, test_remove_lines_in_range_and_compress)
{
    BoardImpl board{3, 3};
    board.add_brick(create_rectangle_brick(3, 3, Color::red));
    board.remove_brick({{ {{0, 0}} }});
    BoardImpl board2{board};
    
    int lines = board.remove_lines_in_range_and_compress(0, 0);
    ASSERT_EQ(lines, 0);
    ASSERT_TRUE(board.get_pixels() == board2.get_pixels());

    int lines2 = board.remove_lines_in_range_and_compress(0, 2);
    ASSERT_EQ(lines2, 2);
    vector<vector<Pixel>> pixels = board.get_pixels();
    const Brick brick{{ {{2, 1}, Color::red}, {{2, 2}, Color::red} }};
    foreach_pixel(pixels, [brick](vector<vector<Pixel>> pixels, int x, int y)-> void{
        bool is_in_brick = (find(brick.pixels.begin(), brick.pixels.end(), pixels[y][x]) != brick.pixels.end());
        ASSERT_TRUE(pixels[y][x].empty() == not is_in_brick);
    });
}