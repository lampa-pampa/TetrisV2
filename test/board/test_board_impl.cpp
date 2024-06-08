#include "board/board_impl.h"

#include <tuple>
#include <utility>
#include <vector>

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "brick/brick.h"
#include "cube/cube.h"
#include "ui/color/color_id_name.h"

using std::pair;
using std::tuple;
using std::vector;
using testing::Eq;
using Tetris::BoardImpl;
using Tetris::Brick;
using Tetris::Cube;
using Tetris::Ui::ColorIdName;
using CubeMatrix = vector<vector<Cube>>;

TEST(BoardImpl, put_cubes)
{
    BoardImpl initial_board{2};
    const vector<pair<vector<Cube>, CubeMatrix>> cubes_to_expected{
        {
            {
                {0, 0, ColorIdName::white},
                {0, 1, ColorIdName::white},
            },
            {
                {
                    {{0, 0, ColorIdName::white}, {1, 0}},
                    {{0, 1, ColorIdName::white}, {1, 1}},
                },
            },
        },
        {
            {
                {0, 1, ColorIdName::white},
                {1, 1, ColorIdName::white},
            },
            {
                {
                    {0, 0},
                    {1, 0},
                },
                {
                    {0, 1, ColorIdName::white},
                    {1, 1, ColorIdName::white},
                },
            },
        },
        {
            {
                {0, 0, ColorIdName::white},
                {1, 1, ColorIdName::white},
            },
            {
                {
                    {0, 0, ColorIdName::white},
                    {1, 0},
                },
                {
                    {0, 1},
                    {1, 1, ColorIdName::white},
                },
            },
        },
    };

    for (const auto& pair : cubes_to_expected)
    {
        BoardImpl board{initial_board};
        board.put_cubes(pair.first);

        ASSERT_THAT(board.get_cubes(), Eq(pair.second));
    }
};

TEST(BoardImpl, remove_lines_and_compress)
{
    const BoardImpl initial_board{{2, 3}};
    const vector<
        pair<tuple<vector<Cube>, int, int>, tuple<CubeMatrix, vector<int>>>>
        cubes_and_range_to_expected{
            {
                {
                    {
                        {0, 1, ColorIdName::white},
                        {0, 2, ColorIdName::white},
                        {1, 2, ColorIdName::white},
                    },
                    0,
                    2,
                },
                {
                    {
                        {
                            {0, 0},
                            {1, 0},
                        },
                        {
                            {0, 1},
                            {1, 1},
                        },
                        {
                            {0, 2, ColorIdName::white},
                            {1, 2},
                        },
                    },
                    {2},
                },
            },
            {
                {
                    {
                        {0, 1, ColorIdName::white},
                        {1, 1, ColorIdName::white},
                        {0, 2, ColorIdName::white},
                    },
                    2,
                    2,
                },
                {
                    {
                        {
                            {0, 0},
                            {1, 0},
                        },
                        {
                            {0, 1, ColorIdName::white},
                            {1, 1, ColorIdName::white},
                        },
                        {
                            {0, 2, ColorIdName::white},
                            {1, 2},
                        },
                    },
                    {},
                },
            },
            {
                {
                    {
                        {0, 1, ColorIdName::white},
                        {1, 1, ColorIdName::white},
                        {0, 2, ColorIdName::white},
                        {1, 2, ColorIdName::white},
                    },
                    1,
                    2,
                },
                {
                    {
                        {
                            {0, 0},
                            {1, 0},
                        },
                        {
                            {0, 1},
                            {1, 1},
                        },
                        {
                            {0, 2},
                            {1, 2},
                        },
                    },
                    {1, 2},
                },
            },
        };

    for (const auto& pair : cubes_and_range_to_expected)
    {
        const auto& [initial_cubes, from_y, to_y]{pair.first};
        const auto& [expected_cubes, expected_row_indexes]{pair.second};
        BoardImpl board{initial_board};
        board.put_cubes(initial_cubes);
        const vector actual{board.remove_lines_and_compress(from_y, to_y)};

        ASSERT_THAT(actual, Eq(expected_row_indexes));
        ASSERT_THAT(board.get_cubes(), Eq(expected_cubes));
    }
}

TEST(BoardImpl, brick_is_valid)
{
    const vector<Cube> initial_cubes{
        {1, 1, ColorIdName::white},
    };
    const vector<pair<Brick, bool>> brick_to_expected{
        {
            {{{0, 0}, {0, 1}}, ColorIdName::white},
            true,
        },
        {
            {{{0, 1}, {1, 1}}, ColorIdName::white},
            false,
        },
        {
            {{{0, 1}, {0, 2}}, ColorIdName::white},
            false,
        },
        {
            {{{-1, 0}, {0, 0}}, ColorIdName::white},
            false,
        },
        {
            {{{0, 1}, {0, 2}}, ColorIdName::white},
            false,
        },
        {
            {{{0, -1}, {0, 0}}, ColorIdName::white},
            false,
        },
    };

    BoardImpl board{{2}};
    board.put_cubes(initial_cubes);

    for (const auto& pair : brick_to_expected)
        ASSERT_THAT(board.brick_is_valid(pair.first), Eq(pair.second));
}

TEST(BoardImpl, get_cubes)
{
    const vector<pair<BoardImpl, CubeMatrix>> board_to_expected{
        {
            {{2}},
            {
                {
                    {0, 0},
                    {1, 0},
                },
                {
                    {0, 1},
                    {1, 1},
                },
            },
        },
        {
            {{2, 3}},
            {
                {
                    {0, 0},
                    {1, 0},
                },
                {
                    {0, 1},
                    {1, 1},
                },
                {
                    {0, 2},
                    {1, 2},
                },
            },
        },
        {
            {{3}},
            {
                {
                    {0, 0},
                    {1, 0},
                    {2, 0},
                },
                {
                    {0, 1},
                    {1, 1},
                    {2, 1},
                },
                {
                    {0, 2},
                    {1, 2},
                    {2, 2},
                },
            },
        },
    };

    for (const auto& pair : board_to_expected)
    {
        const CubeMatrix& actual{pair.first.get_cubes()};

        ASSERT_THAT(actual, Eq(pair.second));
    }
}
