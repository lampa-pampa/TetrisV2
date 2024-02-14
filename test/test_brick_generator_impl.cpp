#include "bag.h"
#include "brick.h"
#include "brick_generator_impl.h"
#include "color.h"
#include "rng.h"
#include "rng_mock.h"
#include <gtest/gtest.h>
#include <memory>
#include <vector>

using std::vector;
using std::unique_ptr; 

TEST(BrickGeneratorImpl, test_generate)
{
    const vector<Brick> bricks{
        { { {{1, 0}}, {{0, 1}} }},
        { { {{2, 0}}, {{0, 2}} }},
    };
    const vector<Color> colors{
        Color::red,
        Color::blue,
    };
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{bricks, unique_ptr<RNG>{new RNGMock{}}},
        Bag<Color>{colors, unique_ptr<RNG>{new RNGMock{}}},
    };
    const vector<Brick> expected_bricks{
        {{ {{1, 0}, Color::red}, {{0, 1}, Color::red} }},
        {{ {{2, 0}, Color::blue}, {{0, 2}, Color::blue} }},
    };
    for(const Brick &expected_brick : expected_bricks)
        ASSERT_TRUE(brick_generator.generate() == expected_brick);
}