#include "brick.h"
#include "test_pixel_lists.h"
#include <gtest/gtest.h>

TEST(Brick, test_get_min_x)
{
    Brick brick{test_pixel_lists.at('J'), {1, 2}};
    EXPECT_EQ(brick.get_min_x(), -1);
}