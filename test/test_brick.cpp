#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "brick.h"

using testing::Eq;
using Tetris::Brick;

TEST(Brick, get_colored)
{
    const Brick brick{{ {1, 2}, {3, 4} }};
    const Brick expected_brick{{ {1, 2, 1}, {3, 4, 1} }};
    
    ASSERT_THAT(Brick::get_colored(brick, 1), Eq(expected_brick));
}

TEST(Brick, get_translated)
{
    const Brick brick{{ {1, 2}, {3, 4} }};
    const Brick expected_brick{{ {2, 4}, {4, 6} }};
    
    ASSERT_THAT(Brick::get_translated(brick, {1, 2}), Eq(expected_brick));
}

TEST(Brick, get_rotated_without_moved_center)
{ 
    const Brick brick{{ {1, 2}, {3, 4} }};
    const Brick expected_brick{{ {-1, -2}, {-3, -4} }};
    
    ASSERT_THAT(Brick::get_rotated(brick, 4), Eq(brick));
    ASSERT_THAT(Brick::get_rotated(brick, 2), Eq(expected_brick));
}

TEST(Brick, get_rotated_with_moved_center)
{
    const Brick brick{{ {1, 2}, {3, 4} }, {1, 0}};
    const Brick expected_brick{{ {0, -1}, {-2, -3} }, {1, 0}};
    
    ASSERT_THAT(Brick::get_rotated(brick, 4), Eq(brick));
    ASSERT_THAT(Brick::get_rotated(brick, 2), Eq(expected_brick));
}

TEST(Brick, get_ghostified)
{
    const Brick brick{{ {1, 2}, {3, 4} }};
    const Brick expected_brick{{
        {1, 2, 0, true},
        {3, 4, 0, true},
    }};
    
    ASSERT_THAT(Brick::get_ghostified(brick), Eq(expected_brick));
}

TEST(Brick, get_transformed)
{
    const Brick brick{{ {1, 2}, {3, 4} }};
    const Brick expected_brick{{ {0, 0}, {-2, -2} }};
    
    ASSERT_THAT(Brick::get_transformed(brick, 2, {1, 2}), Eq(expected_brick));
}

TEST(Brick, get_min_x)
{
    const Brick brick{{ {1, 2}, {3, 4} }};
    
    ASSERT_THAT(brick.get_min_x(), Eq(1));
}

TEST(Brick, get_max_x)
{
    const Brick brick{{ {1, 2}, {3, 4} }};
    
    ASSERT_THAT(brick.get_max_x(), Eq(3));
}

TEST(Brick, get_min_y)
{
    const Brick brick{{ {1, 2}, {3, 4} }};
    
    ASSERT_THAT(brick.get_min_y(), Eq(2));
}

TEST(Brick, get_max_y)
{
    const Brick brick{{ {1, 2}, {3, 4} }};
    
    ASSERT_THAT(brick.get_max_y(), Eq(4));
}