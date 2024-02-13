#include "board_impl.h"
#include "pixel.h"
#include <gtest/gtest.h>
#include <vector>

using std::vector;

TEST(BoardImpl, BoardImpl)
{
    int width = 10;
    int height = 20;
    BoardImpl board{width, height};
    vector<vector<Pixel>> pixels = board.get_pixels();
    for(int y{0}; y < height; ++y)
    {
        for(int x{0}; x < width; ++x)
        {
            Pixel expected_pixel{{x, y}};
            ASSERT_TRUE(pixels[y][x] == expected_pixel);
        }
    }
}

TEST(BoardImpl, test_get_width)
{
    BoardImpl board{10, 20};
    ASSERT_EQ(board.get_width(), 10);
}