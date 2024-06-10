#include "cube/cube.h"

#include <utility>
#include <vector>

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using std::pair;
using std::vector;
using testing::Eq;
using Tetris::Cube;
using Tetris::Ui::ColorName;

TEST(Cube, empty)
{
    const vector<pair<Cube, bool>> cube_to_expected{
        {{1, 2}, true},
        {{4, 3, ColorName::black}, true},
        {{6, 7, ColorName::white}, false},
        {{8, 0, ColorName::dodie_yellow}, false},
    };

    for (const auto& pair : cube_to_expected)
        ASSERT_THAT(pair.first.empty(), Eq(pair.second));
}

TEST(Cube, clear)
{
    const vector<pair<Cube, Cube>> cube_to_expected{
        {{1, 2}, {1, 2}},
        {{4, 3, ColorName::black}, {4, 3, ColorName::black}},
        {{6, 7, ColorName::davy_s_grey}, {6, 7}},
        {{8, 0, ColorName::screamin_green}, {8, 0}},
    };

    for (const auto& pair : cube_to_expected)
    {
        Cube cube{pair.first};
        cube.clear();

        ASSERT_THAT(cube, Eq(pair.second));
    }
}
