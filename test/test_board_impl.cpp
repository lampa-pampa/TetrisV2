#include "board_impl.h"

#include <tuple>
#include <utility>
#include <vector>

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "brick.h"
#include "cube.h"

using std::pair;
using std::tuple;
using std::vector;
using testing::Eq;
using Tetris::BoardImpl;
using Tetris::Brick;
using Tetris::Cube;

namespace
{
    using CubeMatrix = vector<vector<Cube>>;
}

TEST(BoardImpl, BoardImpl)
{
    const vector<pair<BoardImpl, CubeMatrix>> board_to_expected{
        { {{1, 3}}, {
            { {0, 0} },
            { {0, 1} },
            { {0, 2} },
        }},
        { {2}, {
            { {0, 0}, {1, 0} },
            { {0, 1}, {1, 1} },
        }},
        { {{3, 2}}, {
            { {0, 0}, {1, 0}, {2, 0} },
            { {0, 1}, {1, 1}, {2, 1} },
        }},
    };

    for (const auto& pair : board_to_expected)
        ASSERT_THAT(pair.first.get_cubes(), Eq(pair.second));
}

TEST(BoardImpl, put_cubes)
{
    BoardImpl initial_board{2};
    const vector<pair<vector<Cube>, CubeMatrix>> cubes_to_expected{
        { { {0, 0, 1}, {0, 1, 1} }, {
            { {0, 0, 1}, {1, 0} },
            { {0, 1, 1}, {1, 1} },
        }},
        { { {0, 1, 1}, {1, 1, 1} }, {
            { {0, 0}, {1, 0} },
            { {0, 1, 1}, {1, 1, 1} },
        }},
        { { {0, 0, 1}, {1, 1, 1} }, {
            { {0, 0, 1}, {1, 0} },
            { {0, 1}, {1, 1, 1} },
        }},
    };

    for (const auto& pair : cubes_to_expected)
    {
        BoardImpl board{initial_board};
        board.put_cubes(pair.first);

        ASSERT_THAT(board.get_cubes(), Eq(pair.second));
    }    
}

TEST(BoardImpl, remove_lines_and_compress)
{
    const BoardImpl initial_board{2};
    const vector<pair<
        tuple<vector<Cube>, int, int>,
        tuple<CubeMatrix, vector<int>>>>cubes_and_range_to_expected
    {
        { {{ {0, 0, 1}, {0, 1, 1}, {1, 1, 1} }, 0, 1}, {
            {{ {0, 0}, {1, 0} },
            { {0, 1, 1}, {1, 1} }},
            {1}
        }},
        { {{ {0, 0, 1}, {1, 0, 1}, {1, 1, 1} }, 1, 1}, {
            {{ {0, 0, 1}, {1, 0, 1} },
            { {0, 1}, {1, 1, 1} }},
            {}
        }},
        { {{ {0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1} }, 0, 1}, {
            {{ {0, 0}, {1, 0} },
            { {0, 1}, {1, 1} }},
            {0, 1}
        }},
    };

    for (const auto& pair : cubes_and_range_to_expected)
    {
        const auto&[initial_cubes, from_y, to_y]{pair.first};
        const auto&[expected_cubes, expected_row_indexes]{pair.second};
        BoardImpl board{initial_board};
        board.put_cubes(initial_cubes);
        
        const vector actual{
            board.remove_lines_and_compress(from_y, to_y)
        };

        ASSERT_THAT(actual, Eq(expected_row_indexes));
        ASSERT_THAT(board.get_cubes(), Eq(expected_cubes));
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

    BoardImpl board{2};
    board.put_cubes(initial_cubes);
    
    for (const auto& pair : brick_to_expected)
        ASSERT_THAT(board.brick_is_valid(pair.first), Eq(pair.second));
}

TEST(BoardImpl, get_width)
{
    const vector<pair<BoardImpl, int>> board_to_expected{
        { {{10, 20}}, 10 },
        { {{2, 10}}, 2 },
        { {{20, 20}}, 20 },
    };

    for (const auto& pair : board_to_expected)
        ASSERT_THAT(pair.first.get_width(), Eq(pair.second));
}

TEST(BoardImpl, get_offset)
{
    const vector<pair<BoardImpl, int>> board_to_expected{
        { {{10, 20}}, 0 },
        { {{10, 20}, 2}, 2 },
        { {{10, 20}, 5}, 5 },
    };

    for (const auto& pair : board_to_expected)
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
        BoardImpl board{2, pair.first};
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
        BoardImpl board{2, pair.first};
        board.put_cubes(brick_cubes);
        const vector<Cube>& actual{board.get_visible_brick_cubes(brick_cubes)};

        ASSERT_THAT(actual, Eq(pair.second));
    }    
}