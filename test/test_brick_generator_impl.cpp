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

namespace {
    const vector<Brick> bricks{
        { { {{1, 0}}, {{0, 1}} }, false },
        { { {{2, 0}}, {{0, 2}} }, false },
    };
    const vector<Color> colors{
        Color::red,
        Color::blue,
    };
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{bricks, unique_ptr<RNG>{new RNGMock{}}},
        Bag<Color>{colors, unique_ptr<RNG>{new RNGMock{}}},
    };
}

TEST(BrickGeneratorImpl, get_colored_brick)
{
    const Brick brick{{ {{1, 0}, Color::green}, {{0, 1}, Color::yellow} }, false};    
    const Brick expected_brick{{ {{1, 0}, Color::red}, {{0, 1}, Color::red} }, false};
    ASSERT_TRUE(brick_generator.get_colored_brick(brick, Color::red) == expected_brick);
}    

TEST(BrickGeneratorImpl, test_generate)
{
    const vector<Brick> expected_bricks{
        {{ {{1, 0}, Color::red}, {{0, 1}, Color::red} }, false},
        {{ {{2, 0}, Color::blue}, {{0, 2}, Color::blue} }, false},
    };
    for(const Brick &expected_brick : expected_bricks)
        ASSERT_TRUE(brick_generator.generate() == expected_brick);
}