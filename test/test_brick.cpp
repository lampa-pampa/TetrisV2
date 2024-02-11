#include "brick_sources.h"
#include <gtest/gtest.h>

TEST(Brick, test_get_min_x)
{
    EXPECT_EQ(brick_sources.at('J').get_min_x(), -1);
}

TEST(Brick, test_get_max_x)
{
    EXPECT_EQ(brick_sources.at('T').get_max_x(), 1);
}

TEST(Brick, test_get_min_y)
{
    EXPECT_EQ(brick_sources.at('L').get_min_y(), -1);
}

TEST(Brick, test_get_max_y)
{
    EXPECT_EQ(brick_sources.at('O').get_max_y(), 1);
}