#include "color.h"
#include "pixel.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::Eq;
using Tetris::Pixel;
using Tetris::Color;

TEST(Pixel, empty_color_black_ghost_false)
{
    Pixel pixel{0, 0, Color::black};
    
    ASSERT_THAT(pixel.empty(), Eq(true));
}

TEST(Pixel, empty_color_red_ghost_false)
{
    Pixel pixel{0, 0, Color::red};
    
    ASSERT_THAT(pixel.empty(), Eq(false));
}

TEST(Pixel, empty_color_yellow_ghost_true)
{
    Pixel pixel{0, 0, Color::yellow, true};
    
    ASSERT_THAT(pixel.empty(), Eq(false));
}

TEST(Pixel, clear)
{
    Pixel pixel{1, 2, Color::purple, true};
    Pixel expected_pixel{1, 2, Color::black, false};
    pixel.clear();
    
    ASSERT_THAT(pixel, Eq(expected_pixel));
}