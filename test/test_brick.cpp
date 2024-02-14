#include "brick.h"
#include <gtest/gtest.h>

namespace {
    const Brick brick{{ {{1, 2}}, {{3, 4}} }};
}

TEST(Brick, get_colored)
{
    const Brick expected_brick{{ {{1, 2}, Color::red}, {{3, 4}, Color::red} }};
    ASSERT_TRUE(Brick::get_colored(brick, Color::red) == expected_brick);
}

TEST(Brick, get_translated)
{
    const Brick expected_brick{{ {{2, 4}}, {{4, 6}} }};
    ASSERT_TRUE(Brick::get_translated(brick, {1, 2}) == expected_brick);
}

TEST(Brick, get_rotated)
{

    ASSERT_TRUE(Brick::get_rotated(brick, 4) == brick);
    
    const Brick expected_brick{{ {{-1, -2}}, {{-3, -4}} }};
    ASSERT_TRUE(Brick::get_rotated(brick, 2) == expected_brick);

    const Brick brick2{{ {{1, 2}}, {{3, 4}} }, true};
    ASSERT_TRUE(Brick::get_rotated(brick2, 4) == brick2);
    
    const Brick expected_brick2{{ {{0, -1}}, {{-2, -3}} }, true};
    ASSERT_TRUE(Brick::get_rotated(brick2, 2) == expected_brick2);
}

TEST(Brick, get_ghostified)
{
    const Brick expected_brick{{ {{1, 2}, Color::black, true}, {{3, 4}, Color::black, true} }};
    ASSERT_TRUE(Brick::get_ghostified(brick) == expected_brick);
}

TEST(Brick, get_transformed)
{
    const Brick expected_brick{{ {{0, 0}}, {{-2, -2}} }};
    ASSERT_TRUE(Brick::get_transformed(brick, 2, {1, 2}) == expected_brick);
}

TEST(Brick, test_get_min_x)
{
    EXPECT_EQ(brick.get_min_x(), 1);
}

TEST(Brick, test_get_max_x)
{
    EXPECT_EQ(brick.get_max_x(), 3);
}

TEST(Brick, test_get_min_y)
{
    EXPECT_EQ(brick.get_min_y(), 2);
}

TEST(Brick, test_get_max_y)
{
    EXPECT_EQ(brick.get_max_y(), 4);
}