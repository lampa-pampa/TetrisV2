#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "color.h"
#include "pixel.h"

using testing::Eq;
using Tetris::Color;
using Tetris::Pixel;

TEST(Pixel, empty_color_black_ghost_false)
{
    const Pixel pixel{0, 0, Color::black};
    
    ASSERT_THAT(pixel.empty(), Eq(true));
}

TEST(Pixel, empty_color_red_ghost_false)
{
    const Pixel pixel{0, 0, Color::red};
    
    ASSERT_THAT(pixel.empty(), Eq(false));
}

TEST(Pixel, empty_color_yellow_ghost_true)
{
    const Pixel pixel{0, 0, Color::yellow, true};
    
    ASSERT_THAT(pixel.empty(), Eq(false));
}

TEST(Pixel, clear)
{
    Pixel pixel{1, 2, Color::purple, true};
    const Pixel expected_pixel{1, 2, Color::black, false};
    pixel.clear();
    
    ASSERT_THAT(pixel, Eq(expected_pixel));
}