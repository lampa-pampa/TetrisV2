#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "cube.h"

using testing::Eq;
using Tetris::Cube;

TEST(Cube, empty_color_black)
{
    const Cube cube{0, 0, 0};
    
    ASSERT_THAT(cube.empty(), Eq(true));
}

TEST(Cube, empty_color_red)
{
    const Cube cube{0, 0, 1};
    
    ASSERT_THAT(cube.empty(), Eq(false));
}

TEST(Cube, clear)
{
    Cube cube{1, 2, 5};
    const Cube expected_cube{1, 2, 0};
    cube.clear();
    
    ASSERT_THAT(cube, Eq(expected_cube));
}