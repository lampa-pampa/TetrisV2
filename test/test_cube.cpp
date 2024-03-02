#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "cube.h"

using testing::Eq;
using Tetris::Cube;

TEST(Cube, empty_color_black_ghost_false)
{
    const Cube cube{0, 0, 0};
    
    ASSERT_THAT(cube.empty(), Eq(true));
}

TEST(Cube, empty_color_red_ghost_false)
{
    const Cube cube{0, 0, 1};
    
    ASSERT_THAT(cube.empty(), Eq(false));
}

TEST(Cube, empty_color_yellow_ghost_true)
{
    const Cube cube{0, 0, 4, true};
    
    ASSERT_THAT(cube.empty(), Eq(false));
}

TEST(Cube, clear)
{
    Cube cube{1, 2, 5, true};
    const Cube expected_cube{1, 2, 0, false};
    cube.clear();
    
    ASSERT_THAT(cube, Eq(expected_cube));
}