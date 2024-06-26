#include "brick/brick.h"

#include <tuple>
#include <utility>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "brick/brick_name.h"
#include "cube/cube.h"
#include "vector2/vector2.h"

using boost::irange;
using std::pair;
using std::tuple;
using std::vector;
using testing::Eq;
using Tetris::Brick;
using Tetris::BrickName;
using Tetris::Cube;
using Tetris::Vector2;

TEST(Brick, compute_next_rotation)
{
    const int initial_rotation{};
    const vector<pair<int, int>> test_cases{
        {0, 0},
        {3, 3},
        {-1, 3},
        {4, 0},
        {-2, 2},
        {-4, 0},
    };

    for (const auto& pair : test_cases)
    {
        const int actual{
            Brick::compute_next_rotation(initial_rotation, pair.first)};

        ASSERT_THAT(actual, Eq(pair.second));
    }
}

TEST(Brick, get_cubes)
{
    const vector<pair<Brick, vector<Cube>>> test_cases{
        {
            {{{2, 8}}, BrickName::I},
            {
                {2, 8, BrickName::I},
            },
        },
        {
            {{{3, 12}, {6, 4}}, BrickName::I},
            {
                {3, 12, BrickName::I},
                {6, 4, BrickName::I},
            },
        },
        {
            {{{2, 2}, {2, 1}, {1, 2}}, BrickName::I},
            {
                {2, 2, BrickName::I},
                {2, 1, BrickName::I},
                {1, 2, BrickName::I},
            },
        },
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first.get_cubes(), Eq(pair.second));
}

TEST(Brick, get_translated)
{
    const Brick initial_brick{{{6, 3}, {2, 4}}};
    const vector<pair<Vector2, Brick>> test_cases{
        {{4, 9}, {{{10, 12}, {6, 13}}}},
        {{2, -7}, {{{8, -4}, {4, -3}}}},
        {{-3, 5}, {{{3, 8}, {-1, 9}}}},
        {{-4, -8}, {{{2, -5}, {-2, -4}}}},
    };

    for (const auto& pair : test_cases)
    {
        const Brick actual{Brick::get_translated(initial_brick, pair.first)};

        ASSERT_THAT(actual, Eq(pair.second));
    }
}

TEST(Brick, get_rotated)
{
    const vector<pair<Brick, vector<Brick>>> test_cases{
        {
            {{{8, 3}, {4, 5}}},
            {
                {{{8, 3}, {4, 5}}},
                {{{-3, 8}, {-5, 4}}},
                {{{-8, -3}, {-4, -5}}},
                {{{3, -8}, {5, -4}}},
            },
        },
        {
            {{{1, 2}, {6, 3}}, BrickName::I, {2, 4}},
            {
                {{{1, 2}, {6, 3}}, BrickName::I, {2, 4}},
                {{{0, 5}, {-1, 10}}, BrickName::I, {2, 4}},
                {{{-3, 4}, {-8, 3}}, BrickName::I, {2, 4}},
                {{{-2, 1}, {-1, -4}}, BrickName::I, {2, 4}},
            },
        },
    };

    for (const auto& pair : test_cases)
    {
        for (const auto& i : irange(Brick::rotation_count))
        {
            const Brick actual{Brick::get_rotated(pair.first, i)};

            ASSERT_THAT(actual, Eq(pair.second[i]));
        }
    }
}

TEST(Brick, get_transformed)
{
    const Brick initial_brick{{{3, 2}, {4, 1}}};
    const vector<pair<tuple<int, Vector2>, Brick>> test_cases{
        {{1, {2, 3}}, {{{0, 6}, {1, 7}}}},
        {{2, {6, 9}}, {{{3, 7}, {2, 8}}}},
        {{3, {5, 8}}, {{{7, 5}, {6, 4}}}},
    };

    for (const auto& pair : test_cases)
    {
        const auto& [rotation, position]{pair.first};
        const Brick actual{
            Brick::get_transformed(initial_brick, rotation, position)};

        ASSERT_THAT(actual, Eq(pair.second));
    }
}

TEST(Brick, get_min_x)
{
    const vector<pair<Brick, int>> test_cases{
        {{{{3, 4}, {9, 8}}}, 3},
        {{{{0, -6}, {-2, 5}}}, -2},
        {{{{1, -9}, {1, -4}}}, 1},
        {{{}}, 0},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first.get_min_x(), Eq(pair.second));
}

TEST(Brick, get_max_x)
{
    const vector<pair<Brick, int>> test_cases{
        {{{{6, -2}, {-7, 3}}}, 6},
        {{{{10, 1}, {5, -4}}}, 10},
        {{{{3, -9}, {3, 8}}}, 3},
        {{{}}, 0},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first.get_max_x(), Eq(pair.second));
}

TEST(Brick, get_min_y)
{
    const vector<pair<Brick, int>> test_cases{
        {{{{3, 5}, {9, -2}}}, -2},
        {{{{1, -7}, {3, 4}}}, -7},
        {{{{-9, -2}, {-8, -2}}}, -2},
        {{{}}, 0},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first.get_min_y(), Eq(pair.second));
}

TEST(Brick, get_max_y)
{
    const vector<pair<Brick, int>> test_cases{
        {{{{2, 9}, {-6, 1}}}, 9},
        {{{{-5, 0}, {7, 4}}}, 4},
        {{{{6, -3}, {-1, -3}}}, -3},
        {{{}}, 0},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first.get_max_y(), Eq(pair.second));
}

TEST(Brick, get_size)
{
    const vector<pair<Brick, Vector2>> test_cases{
        {{{{-4, 2}, {1, 5}}}, {6, 4}},
        {{{{3, 8}, {-7, 3}}}, {11, 6}},
        {{{{2, -6}, {2, 0}}}, {1, 7}},
        {{{}}, {0, 0}},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first.get_size(), Eq(pair.second));
}
