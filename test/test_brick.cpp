#include "brick.h"
#include "test_pixel_lists.h"
#include <gtest/gtest.h>

TEST(Brick, test_get_min_x)
{
    Brick brick{test_pixel_lists.at('J'), {1, 2}};
    EXPECT_EQ(brick.get_min_x(), -1);
}

TEST(Brick, test_get_min_y)
{
    Brick brick{test_pixel_lists.at('L'), {1, 2}};
    EXPECT_EQ(brick.get_min_y(), -1);
}

TEST(Brick, test_get_max_x)
{
    Brick brick{test_pixel_lists.at('T'), {1, 2}};
    EXPECT_EQ(brick.get_max_x(), 1);
}

TEST(Brick, test_get_max_y)
{
    Brick brick{test_pixel_lists.at('O'), {1, 2}};
    EXPECT_EQ(brick.get_max_y(), 1);
}