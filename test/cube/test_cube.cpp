#include "cube/cube.h"

#include <utility>
#include <vector>

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "brick/brick_name.h"

using std::pair;
using std::vector;
using testing::Eq;
using Tetris::BrickName;
using Tetris::Cube;

TEST(Cube, empty)
{
    const vector<pair<Cube, bool>> cube_to_expected{
        {{1, 2}, true},
        {{4, 3, BrickName::empty}, true},
        {{6, 7, BrickName::i}, false},
        {{8, 0, BrickName::o}, false},
    };

    for (const auto& pair : cube_to_expected)
        ASSERT_THAT(pair.first.empty(), Eq(pair.second));
}

TEST(Cube, clear)
{
    const vector<pair<Cube, Cube>> cube_to_expected{
        {{1, 2}, {1, 2}},
        {{4, 3, BrickName::empty}, {4, 3, BrickName::empty}},
        {{6, 7, BrickName::i}, {6, 7, BrickName::empty}},
        {{8, 0, BrickName::o}, {8, 0, BrickName::empty}},
    };

    for (const auto& pair : cube_to_expected)
    {
        Cube cube{pair.first};
        cube.clear();

        ASSERT_THAT(cube, Eq(pair.second));
    }
}
