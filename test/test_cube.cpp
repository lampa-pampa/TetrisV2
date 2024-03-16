#include "cube.h"

#include <utility>
#include <vector>

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using std::pair;
using std::vector;
using testing::Eq;
using Tetris::Cube;

TEST(Cube, empty)
{
    const vector<pair<Cube, bool>> cube_to_expected{
        { {1, 2}, true },
        { {4, 3, 0}, true },
        { {6, 7, 1}, false },
        { {8, 0, 2}, false },
    };

    for (const auto& pair : cube_to_expected)    
        ASSERT_THAT(pair.first.empty(), Eq(pair.second));
}

TEST(Cube, clear)
{
    const vector<pair<Cube, Cube>> cube_to_expected{
        { {1, 2}, {1, 2} },
        { {4, 3, 0}, {4, 3, 0} },
        { {6, 7, 1}, {6, 7} },
        { {8, 0, 2}, {8, 0} },
    };

    for (const auto& pair : cube_to_expected)
    {
        Cube cube{pair.first};
        cube.clear();

        ASSERT_THAT(cube, Eq(pair.second));
    } 
}