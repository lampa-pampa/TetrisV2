#include "color.h"
#include "pixel.h"
#include <gtest/gtest.h>

TEST(Pixel, empty_color_black_ghost_false)
{
    Pixel pixel{0, 0, Color::black};
    
    ASSERT_TRUE(pixel.empty());
}

TEST(Pixel, empty_color_red_ghost_false)
{
    Pixel pixel{0, 0, Color::red};
    
    ASSERT_FALSE(pixel.empty());
}

TEST(Pixel, empty_color_yellow_ghost_true)
{
    Pixel pixel{0, 0, Color::yellow, true};
    
    ASSERT_FALSE(pixel.empty());
}

TEST(Pixel, clear)
{
    Pixel pixel{1, 2, Color::purple, true};
    Pixel expected_pixel{1, 2, Color::black, false};
    pixel.clear();
    
    ASSERT_TRUE(pixel == expected_pixel);
}