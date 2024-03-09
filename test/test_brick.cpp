#include "brick.h"

#include <utility>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "vector_2.h"

using boost::irange;
using std::pair;
using std::vector;
using testing::Eq;
using Tetris::Brick;
using Tetris::Vector2;

namespace
{
    struct TransformArgs
    {
        int rotation;
        Vector2 position;
    };
}

TEST(Brick, compute_next_rotation)
{
    const int initial_rotation{0};
    const vector<pair<int, int>> delta_quarters_to_expected{
        {0, 0},
        {3, 3},
        {-1, 3},
        {4, 0},
        {-2, 2},
        {-4, 0},
    };

    for(const auto& pair: delta_quarters_to_expected)
    {
        const int actual{
            Brick::compute_next_rotation(initial_rotation, pair.first)
        };

        ASSERT_THAT(actual, Eq(pair.second));
    }
}

TEST(Brick, get_translated)
{
    const Brick initial_brick{{ {6, 3}, {2, 4} }};
    const vector<pair<Vector2, Brick>> position_to_expected{
        { {4, 9}, {{ {10, 12}, {6, 13} }} },
        { {2, -7}, {{ {8, -4}, {4, -3} }} },
        { {-3, 5}, {{ {3, 8}, {-1, 9} }} },
        { {-4, -8}, {{ {2, -5}, {-2, -4} }} },
    };

    for(const auto& pair: position_to_expected)
    {
        const Brick actual{Brick::get_translated(initial_brick, pair.first)};

        ASSERT_THAT(actual, Eq(pair.second));
    }
}

TEST(Brick, get_rotated)
{ 
    const vector<pair<Brick, vector<Brick>>> brick_to_expected{
        { {{ {8, 3}, {4, 5} }}, {
            {{ {8, 3}, {4, 5} }},
            {{ {-3, 8}, {-5, 4} }},
            {{ {-8, -3}, {-4, -5} }},
            {{ {3, -8}, {5, -4} }},
        }},
        { {{ {1, 2}, {6, 3} }, {2, 4} }, {
            {{ {1, 2}, {6, 3} }, {2, 4} },
            {{ {0, 5}, {-1, 10} }, {2, 4} },
            {{ {-3, 4}, {-8, 3} }, {2, 4} },
            {{ {-2, 1}, {-1, -4} }, {2, 4} },
        }},
    };

    for(const auto& pair: brick_to_expected)
    {
        for(const auto& i : irange(Brick::rotation_quantity))
        {
            const Brick actual{Brick::get_rotated(pair.first, i)};

            ASSERT_THAT(actual, Eq(pair.second[i]));
        }
    }
}

TEST(Brick, get_transformed)
{
    const Brick initial_brick{{ {3, 2}, {4, 1} }};
    const vector<pair<TransformArgs, Brick>> args_to_expected{
        { { 1, {2, 3} }, {{ {0, 6}, {1, 7} }} },
        { { 2, {6, 9} }, {{ {3, 7}, {2, 8} }} },
        { { 3, {5, 8} }, {{ {7, 5}, {6, 4} }} },
    };

    for(const auto& pair: args_to_expected)
    {
        const TransformArgs args{pair.first};
        const Brick actual{
            Brick::get_transformed(
                initial_brick, args.rotation, args.position)
        };

        ASSERT_THAT(actual, Eq(pair.second));
    }
}

TEST(Brick, get_min_x)
{
    const vector<pair<Brick, int>> brick_to_expected{
        { {{ {3, 4}, {9, 8} }}, 3 },
        { {{ {0, -6}, {-2, 5} }}, -2 },
        { {{ {1, -9}, {1, -4} }}, 1 },
        { {{}}, 0 },
    };

    for(const auto& pair: brick_to_expected)
        ASSERT_THAT(pair.first.get_min_x(), Eq(pair.second));
}

TEST(Brick, get_max_x)
{
    const vector<pair<Brick, int>> brick_to_expected{
        { {{ {6, -2}, {-7, 3} }}, 6 },
        { {{ {10, 1}, {5, -4} }}, 10 },
        { {{ {3, -9}, {3, 8} }}, 3 },
        { {{}}, 0 },
    };

    for(const auto& pair: brick_to_expected)
        ASSERT_THAT(pair.first.get_max_x(), Eq(pair.second));
}

TEST(Brick, get_min_y)
{
   const vector<pair<Brick, int>> brick_to_expected{
        { {{ {3, 5}, {9, -2} }}, -2 },
        { {{ {1, -7}, {3, 4} }}, -7 },
        { {{ {-9, -2}, {-8, -2} }}, -2 },
        { {{}}, 0 },
    };

    for(const auto& pair: brick_to_expected)
        ASSERT_THAT(pair.first.get_min_y(), Eq(pair.second));
}

TEST(Brick, get_max_y)
{
    const vector<pair<Brick, int>> brick_to_expected{
        { {{ {2, 9}, {-6, 1} }}, 9 },
        { {{ {-5, 0}, {7, 4} }}, 4 },
        { {{ {6, -3}, {-1, -3} }}, -3 },
        { {{}}, 0 },
    };

    for(const auto& pair: brick_to_expected)
        ASSERT_THAT(pair.first.get_max_y(), Eq(pair.second));
}

TEST(Brick, get_width)
{
    const vector<pair<Brick, int>> brick_to_expected{
        { {{ {-4, 2}, {1, 5} }}, 6 },
        { {{ {3, 8}, {-7, 3} }}, 11 },
        { {{ {2, -6}, {2, 0} }}, 1 },
        { {{}}, 0 },
    };

    for(const auto& pair: brick_to_expected)
        ASSERT_THAT(pair.first.get_width(), Eq(pair.second));
}

TEST(Brick, get_height)
{
    const vector<pair<Brick, int>> brick_to_expected{
        { {{ {1, 3}, {2, -6} }}, 10 },
        { {{ {-7, 7}, {3, 4} }}, 4 },
        { {{ {9, -5}, {-2, -5} }}, 1 },
        { {{}}, 0 },
    };

    for(const auto& pair: brick_to_expected)
        ASSERT_THAT(pair.first.get_height(), Eq(pair.second));
}