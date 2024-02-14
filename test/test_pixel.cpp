#include "color.h"
#include "pixel.h"
#include <gtest/gtest.h>

TEST(Pixel, test_empty)
{
    Pixel pixel1{{0, 0}, Color::black};
    ASSERT_EQ(pixel1.empty(), true);

    Pixel pixel2{{0, 0}, Color::red};
    ASSERT_EQ(pixel2.empty(), false);
        
    Pixel pixel3{{0, 0}, Color::yellow, true};
    ASSERT_EQ(pixel3.empty(), true);
}

TEST(Pixel, test_clear)
{
    Pixel pixel{{1, 2}, Color::purple, true};
    Pixel expected_pixel{{1, 2}, Color::black, false};
    pixel.clear();
    ASSERT_TRUE(pixel == expected_pixel);
}