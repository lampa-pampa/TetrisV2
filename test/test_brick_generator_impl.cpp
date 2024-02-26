#include "bag.h"
#include "brick.h"
#include "brick_generator_impl.h"
#include "color.h"
#include "rng_mock.h"
#include <gtest/gtest.h>
#include <vector>

using std::vector;

TEST(BrickGeneratorImpl, generate)
{
    const vector<Brick> bricks{
        {{ {1, 0}, {0, 1} }},
        {{ {2, 0}, {0, 2} }},
    };
    const vector<Color> colors{
        Color::red,
        Color::blue,
    };
    RNGMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag<Brick>{bricks, rng},
        Bag<Color>{colors, rng},
    };
    const vector<Brick> expected_bricks{
        {{ {1, 0, Color::red}, {0, 1, Color::red} }},
        {{ {2, 0, Color::blue}, {0, 2, Color::blue} }},
    };
    for(int i{0}; i < 2; ++i)
    {
        for(const Brick &expected_brick : expected_bricks)
            ASSERT_TRUE(brick_generator.generate() == expected_brick);
    }
}