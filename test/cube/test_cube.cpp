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
    const vector<pair<Cube, bool>> test_cases{
        {{1, 2}, true},
        {{4, 3, BrickName::empty}, true},
        {{6, 7, BrickName::I}, false},
        {{8, 0, BrickName::O}, false},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first.empty(), Eq(pair.second));
}

TEST(Cube, clear)
{
    const vector<pair<Cube, Cube>> test_cases{
        {{1, 2}, {1, 2}},
        {{4, 3, BrickName::empty}, {4, 3, BrickName::empty}},
        {{6, 7, BrickName::I}, {6, 7, BrickName::empty}},
        {{8, 0, BrickName::O}, {8, 0, BrickName::empty}},
    };

    for (const auto& pair : test_cases)
    {
        Cube cube{pair.first};
        cube.clear();

        ASSERT_THAT(cube, Eq(pair.second));
    }
}
