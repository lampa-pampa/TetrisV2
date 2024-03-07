#include <gmock/gmock-matchers.h>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "board_impl.h"
#include "brick.h"
#include "cube.h"

using std::pair;
using std::vector;
using testing::Eq;
using Tetris::BoardImpl;
using Tetris::Brick;
using Tetris::Cube;

namespace
{
    using CubeMatrix = vector<vector<Cube>>;
    
    struct Range
    {
        int from_y;
        int to_y;
    };
}


TEST(BoardImpl, BoardImpl)
{
    const CubeMatrix expected_board_cubes{
        { {0, 0}, {1, 0} },
        { {0, 1}, {1, 1} },
    };

    BoardImpl board{2, 2};

    ASSERT_THAT(board.get_cubes(), Eq(expected_board_cubes));
}

TEST(BoardImpl, put_cubes)
{
    const Brick brick{{ {0, 0, 1}, {0, 1, 1} }};
    const CubeMatrix expected_board_cubes{
        { {0, 0, 1}, {1, 0} },
        { {0, 1, 1}, {1, 1} },
    };

    BoardImpl board{2, 2};
    board.put_cubes(brick.cubes);
    
    ASSERT_THAT(board.get_cubes(), Eq(expected_board_cubes));
}

TEST(BoardImpl, remove_lines_and_compress__return_value)
{
    const vector<pair<vector<Cube>, vector<int>>> initial_cubes_to_expected{
        { { {0, 0, 1}, {0, 1, 1} }, {} },
        { { {0, 0, 1}, {1, 0, 1} }, {0} },
        { { {0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1} }, {0, 1} },
    };
    const Range range{0, 1};

    for (const auto& pair : initial_cubes_to_expected)
    {
        BoardImpl board{2, 2};
        board.put_cubes(pair.first);
        const vector actual{
            board.remove_lines_and_compress(range.from_y, range.to_y)
        };

        ASSERT_THAT(actual, Eq(pair.second));
    }    
}

TEST(BoardImpl, remove_lines_and_compress__range)
{
    const vector<Cube> initial_cubes{
        {0, 0, 1}, {1, 0, 1}, {0, 2, 1}, {1, 2, 1}
    };
    const vector<pair<Range, vector<int>>> range_to_expected{
        { {1, 1}, {} },
        { {0, 0}, {0} },
        { {0, 2}, {0, 2} },
    };

    for (const auto& pair : range_to_expected)
    {
        BoardImpl board{2, 3};
        board.put_cubes(initial_cubes);
        const vector actual{
            board.remove_lines_and_compress(pair.first.from_y, pair.first.to_y)
        };

        ASSERT_THAT(actual, Eq(pair.second));
    }    
}

TEST(BoardImpl, remove_lines_and_compress__cubes)
{
    const vector<pair<vector<Cube>, CubeMatrix>> initial_cubes_to_expected{
        { { {0, 0, 1}, {0, 1, 1}, {1, 1, 1} }, {
            { {0, 0}, {1, 0} },
            { {0, 1, 1}, {1, 1} },
        }},
        { { {0, 0, 1}, {1, 1, 1} }, {
            { {0, 0, 1}, {1, 0} },
            { {0, 1}, {1, 1, 1} },
        }},
        { { {0, 0, 1}, {1, 0, 1} }, {
            { {0, 0}, {1, 0} },
            { {0, 1}, {1, 1} },
        }},
    };
    const Range range{0, 1};

    for (const auto& pair : initial_cubes_to_expected)
    {
        BoardImpl board{2, 2};
        board.put_cubes(pair.first);
        board.remove_lines_and_compress(range.from_y, range.to_y);

        ASSERT_THAT(board.get_cubes(), Eq(pair.second));
    }    
}

TEST(BoardImpl, brick_is_valid)
{
    const vector<Cube> initial_cubes{ {1, 1, 1} };
    const vector<pair<Brick, bool>> brick_to_expected{
        { {{ {0, 0, 1}, {0, 1, 1} }}, true },
        { {{ {0, 1, 1}, {1, 1, 1} }}, false },
        { {{ {0, 1, 1}, {0, 2, 1} }}, false },
        { {{ {-1, 0, 1}, {0, 0, 1} }}, false },
        { {{ {0, 1, 1}, {0, 2, 1} }}, false },
        { {{ {0, -1, 1}, {0, 0, 1} }}, false },
    };

    BoardImpl board{2, 2};
    board.put_cubes(initial_cubes);
    
    for (const auto& pair : brick_to_expected)
        ASSERT_THAT(board.brick_is_valid(pair.first), Eq(pair.second));
}

TEST(BoardImpl, get_width)
{
    BoardImpl board{10, 20};

    ASSERT_THAT(board.get_width(), Eq(10));
}

TEST(BoardImpl, get_offset)
{
    const vector<pair<BoardImpl, int>> board_to_expected{
        { {10, 20}, 0 },
        { {10, 20, 2}, 2 },
    };

    for(const auto& pair : board_to_expected)
        ASSERT_THAT(pair.first.get_offset(), Eq(pair.second));
}

TEST(BoardImpl, get_visible_cubes)
{
    const vector<Cube> initial_cubes{ {0, 0, 1}, {1, 0, 1}, {0, 1, 1} };
    const vector<pair<int, CubeMatrix>> offset_to_expected{
        { 0, { 
            { {0, 0, 1}, {1, 0, 1} },
            { {0, 1, 1}, {1, 1} },
        }},
        { 1, {
            { {0, 1, 1}, {1, 1} },
            { {0, 2}, {1, 2} },
        }},
        { 2, {
            { {0, 2}, {1, 2} },
            { {0, 3}, {1, 3} },
        }},
    };

    for (const auto& pair : offset_to_expected)
    {
        BoardImpl board{2, 2, pair.first};
        board.put_cubes(initial_cubes);

        ASSERT_THAT(board.get_visible_cubes(), Eq(pair.second));
    }    
}

TEST(BoardImpl, get_visible_brick_cubes)
{
    const vector<Cube> brick_cubes{ {0, 0, 1}, {1, 0, 1}, {1, 1, 1} };
    const vector<pair<int, vector<Cube>>> offset_to_expected{
        { 0, { {0, 0, 1}, {1, 0, 1}, {1, 1, 1} } },
        { 1, { {1, 1, 1} } },
        { 2, {} },
    };

    for (const auto& pair : offset_to_expected)
    {
        BoardImpl board{2, 2, pair.first};
        board.put_cubes(brick_cubes);
        const vector<Cube>& actual{board.get_visible_brick_cubes(brick_cubes)};

        ASSERT_THAT(actual, Eq(pair.second));
    }    
}