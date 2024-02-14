#include "color.h"
#include "pixel.h"
#include <gtest/gtest.h>

TEST(Pixel, test_empty)
{
    Pixel pixel1{{0, 0}, Color::black};
    ASSERT_TRUE(pixel1.empty());

    Pixel pixel2{{0, 0}, Color::red};
    ASSERT_FALSE(pixel2.empty());
        
    Pixel pixel3{{0, 0}, Color::yellow, true};
    ASSERT_TRUE(pixel3.empty());
}

TEST(Pixel, test_clear)
{
    Pixel pixel{{1, 2}, Color::purple, true};
    Pixel expected_pixel{{1, 2}, Color::black, false};
    pixel.clear();
    ASSERT_TRUE(pixel == expected_pixel);
}