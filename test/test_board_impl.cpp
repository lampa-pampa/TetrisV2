#include <algorithm>
#include <functional>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "board_impl.h"
#include "brick.h"
#include "cube.h"

using boost::irange;
using std::find;
using std::function;
using std::vector;
using testing::Eq;
using Tetris::BoardImpl;
using Tetris::Brick;
using Tetris::Cube;

namespace {
    using CubeMatrix = vector<vector<Cube>>;

    vector<Cube> create_rectangle_shape(int width, int height, int color_code)
    {
        vector<Cube> shape{};
        for (const auto& y : irange(height))
        {
            for (const auto& x : irange(width))
                shape.emplace_back(Cube{x, y, color_code});
        }
        return shape;
    }
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

TEST(BoardImpl, BoardImpl)
{
    BoardImpl board{2, 2};
    const vector<Cube> expected_board_cubes{
        {0, 0}, {1, 0},
        {0, 1}, {1, 1},
    };
    const CubeMatrix board_cubes{board.get_cubes()};
    
    for_each_cube_assert_true(
        board_cubes,
        [expected_board_cubes](Cube cube){
            return is_in(cube, expected_board_cubes);
        }
    );
}

TEST(BoardImpl, is_space_for_brick_empty_board)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {0, 0} }};
    
    ASSERT_THAT(board.is_space_for_brick(brick.cubes), Eq(true));
}

TEST(BoardImpl, is_space_for_brick_off_range)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {1, 3} }};
    
    ASSERT_THAT(board.is_space_for_brick(brick.cubes), Eq(false));
}

TEST(BoardImpl, is_space_for_brick_filled_board)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {0, 0} }};
    board.put_cubes(create_rectangle_shape(3, 3, 1));
    
    ASSERT_THAT(board.is_space_for_brick(brick.cubes), Eq(false));    
}

TEST(BoardImpl, put_cubes)
{
    BoardImpl board{3, 3};
    const Brick brick{{ {1, 2, 2}, {2, 2, 2} }};
    board.put_cubes(brick.cubes);
    const CubeMatrix board_cubes{board.get_cubes()};
    
    for_each_cube_assert_true(board_cubes, [brick](Cube cube){
        return cube.empty() != is_in(cube, brick.cubes);
    });
}

TEST(BoardImpl, clear_cubes)
{
    BoardImpl board{3, 3};
    board.put_cubes(create_rectangle_shape(3, 3, 1));
    const Brick brick{{ {0, 0}, {0, 1} }};   
    board.clear_cubes(brick.cubes);
    const CubeMatrix board_cubes{board.get_cubes()};
    
    for_each_cube_assert_true(board_cubes, [brick](Cube cube){
        return cube.empty() == is_in(cube, brick.cubes);
    });
}

TEST(BoardImpl, remove_lines_in_range_and_compress_without_lines_in_range)
{
    BoardImpl board{3, 3};
    const Brick brick{create_rectangle_shape(3, 2, 1)};
    board.put_cubes(brick.cubes);
    const int lines{board.remove_lines_in_range_and_compress(2, 2)};
    const CubeMatrix board_cubes{board.get_cubes()};

    
    ASSERT_THAT(lines, Eq(0));
    for_each_cube_assert_true(board_cubes, [brick](Cube cube){
        return cube.empty() != is_in(cube, brick.cubes);
    });
}

TEST(BoardImpl, remove_lines_in_range_and_compress_with_lines_in_range)
{
    BoardImpl board{3, 3};
    board.put_cubes(create_rectangle_shape(3, 2, 1));
    board.put_cubes(create_rectangle_shape(2, 3, 1));
    const Brick brick{{ {0, 2, 1}, {1, 2, 1} }};
    const int lines{board.remove_lines_in_range_and_compress(0, 2)};
    const CubeMatrix board_cubes{board.get_cubes()};
    
    ASSERT_THAT(lines, Eq(2));
    for_each_cube_assert_true(board_cubes, [brick](Cube cube){
        return cube.empty() != is_in(cube, brick.cubes);
    });
}