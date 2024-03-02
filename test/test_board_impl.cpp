#include <algorithm>
#include <functional>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "board_impl.h"
#include "brick.h"
#include "pixel.h"

using boost::irange;
using std::find;
using std::function;
using std::vector;
using testing::Eq;
using Tetris::BoardImpl;
using Tetris::Brick;
using Tetris::Pixel;

namespace {
    using Pixels = vector<vector<Pixel>>;

    vector<Pixel> create_rectangle_shape(int width, int height, int color_code)
    {
        vector<Pixel> shape{};
        for (const auto& y : irange(height))
        {
            for (const auto& x : irange(width))
                shape.emplace_back(Pixel{x, y, color_code});
        }
        return shape;
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
    
    ASSERT_THAT(board.is_space_for_brick(brick.pixels), Eq(true));
}

TEST(BoardImpl, is_space_for_brick_off_range)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {1, 3} }};
    
    ASSERT_THAT(board.is_space_for_brick(brick.pixels), Eq(false));
}

TEST(BoardImpl, is_space_for_brick_filled_board)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {0, 0} }};
    board.put_pixels(create_rectangle_shape(3, 3, 1));
    
    ASSERT_THAT(board.is_space_for_brick(brick.pixels), Eq(false));    
}

TEST(BoardImpl, put_pixels)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {1, 2, 2}, {2, 2, 2} }};
    board.put_pixels(brick.pixels);
    const Pixels board_pixels{board.get_pixels()};
    
    for_each_pixel_assert_true(board_pixels, [brick](Pixel pixel){
        return pixel.empty() != is_in(pixel, brick.pixels);
    });
}

TEST(BoardImpl, clear_pixels)
{
    BoardImpl board{3, 3};
    board.put_pixels(create_rectangle_shape(3, 3, 1));
    const Brick brick{{ {0, 0}, {0, 1} }};   
    board.clear_pixels(brick.pixels);
    const Pixels board_pixels{board.get_pixels()};
    
    for_each_pixel_assert_true(board_pixels, [brick](Pixel pixel){
        return pixel.empty() == is_in(pixel, brick.pixels);
    });
}

TEST(BoardImpl, remove_lines_in_range_and_compress_without_lines_in_range)
{
    BoardImpl board{3, 3};
    const Brick brick{create_rectangle_shape(3, 2, 1)};
    board.put_pixels(brick.pixels);
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
    board.put_pixels(create_rectangle_shape(3, 2, 1));
    board.put_pixels(create_rectangle_shape(2, 3, 1));
    const Brick brick{{ {0, 2, 1}, {1, 2, 1} }};
    const int lines{board.remove_lines_in_range_and_compress(0, 2)};
    const Pixels board_pixels{board.get_pixels()};
    
    ASSERT_THAT(lines, Eq(2));
    for_each_pixel_assert_true(board_pixels, [brick](Pixel pixel){
        return pixel.empty() != is_in(pixel, brick.pixels);
    });
}