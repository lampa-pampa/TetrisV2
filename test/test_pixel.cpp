#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "pixel.h"

using testing::Eq;
using Tetris::Pixel;

TEST(Pixel, empty_color_black_ghost_false)
{
    const Pixel pixel{0, 0, 0};
    
    ASSERT_THAT(pixel.empty(), Eq(true));
}

TEST(Pixel, empty_color_red_ghost_false)
{
    const Pixel pixel{0, 0, 1};
    
    ASSERT_THAT(pixel.empty(), Eq(false));
}

TEST(Pixel, empty_color_yellow_ghost_true)
{
    const Pixel pixel{0, 0, 4, true};
    
    ASSERT_THAT(pixel.empty(), Eq(false));
}

TEST(Pixel, clear)
{
    Pixel pixel{1, 2, 5, true};
    const Pixel expected_pixel{1, 2, 0, false};
    pixel.clear();
    
    ASSERT_THAT(pixel, Eq(expected_pixel));
}