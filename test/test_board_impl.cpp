#include <algorithm>
#include <functional>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "board_impl.h"
#include "brick.h"
#include "color.h"
#include "pixel.h"

using boost::irange;
using std::find;
using std::function;
using std::vector;
using testing::Eq;
using Tetris::BoardImpl;
using Tetris::Brick;
using Tetris::Color;
using Tetris::Pixel;

namespace {
    using Pixels = vector<vector<Pixel>>;

    Brick create_rectangle_brick(int width, int height, Color color)
    {
        Brick full_brick{};
        for (const auto& y : irange<int>(height))
        {
            for (const auto& x : irange<int>(width))
                full_brick.pixels.emplace_back(Pixel{x, y, color});
        }
        return full_brick;
    }
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

TEST(BoardImpl, BoardImpl)
{
    BoardImpl board{2, 2};
    const vector<Pixel> expected_board_pixels{
        {0, 0}, {1, 0},
        {0, 1}, {1, 1},
    };
    const Pixels board_pixels{board.get_pixels()};
    
    for_each_pixel_assert_true(
        board_pixels,
        [expected_board_pixels](Pixel pixel){
            return is_in(pixel, expected_board_pixels);
        }
    );
}

TEST(BoardImpl, is_space_for_brick_empty_board)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {0, 0} }};
    
    ASSERT_THAT(board.is_space_for_brick(brick), Eq(true));
}

TEST(BoardImpl, is_space_for_brick_off_range)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {1, 3} }};
    
    ASSERT_THAT(board.is_space_for_brick(brick), Eq(false));
}

TEST(BoardImpl, is_space_for_brick_filled_board)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {0, 0} }};
    board.add_brick(create_rectangle_brick(3, 3, Color::red));
    
    ASSERT_THAT(board.is_space_for_brick(brick), Eq(false));    
}

TEST(BoardImpl, add_brick)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {1, 2, Color::green}, {2, 2, Color::green} }};
    board.add_brick(brick);
    const Pixels board_pixels{board.get_pixels()};
    
    for_each_pixel_assert_true(board_pixels, [brick](Pixel pixel){
        return pixel.empty() != is_in(pixel, brick.pixels);
    });
}

TEST(BoardImpl, remove_brick)
{
    BoardImpl board{3, 3};
    board.add_brick(create_rectangle_brick(3, 3, Color::red));
    const Brick brick{{ {0, 0}, {0, 1} }};   
    board.remove_brick(brick);
    const Pixels board_pixels{board.get_pixels()};
    
    for_each_pixel_assert_true(board_pixels, [brick](Pixel pixel){
        return pixel.empty() == is_in(pixel, brick.pixels);
    });
}

TEST(BoardImpl, remove_lines_in_range_and_compress_without_lines_in_range)
{
    BoardImpl board{3, 3};
    const Brick brick{create_rectangle_brick(3, 2, Color::red)};
    board.add_brick(brick);
    const int lines{board.remove_lines_in_range_and_compress(2, 2)};
    const Pixels board_pixels{board.get_pixels()};

    
    ASSERT_THAT(lines, Eq(0));
    for_each_pixel_assert_true(board_pixels, [brick](Pixel pixel){
        return pixel.empty() != is_in(pixel, brick.pixels);
    });
}

TEST(BoardImpl, remove_lines_in_range_and_compress_with_lines_in_range)
{
    BoardImpl board{3, 3};
    board.add_brick(create_rectangle_brick(3, 2, Color::red));
    board.add_brick(create_rectangle_brick(2, 3, Color::red));
    const Brick brick{{ {0, 2, Color::red}, {1, 2, Color::red} }};
    const int lines{board.remove_lines_in_range_and_compress(0, 2)};
    const Pixels board_pixels{board.get_pixels()};
    
    ASSERT_THAT(lines, Eq(2));
    for_each_pixel_assert_true(board_pixels, [brick](Pixel pixel){
        return pixel.empty() != is_in(pixel, brick.pixels);
    });
}