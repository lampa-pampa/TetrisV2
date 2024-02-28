#include "bag.h"
#include "brick.h"
#include "brick_generator_impl.h"
#include "color.h"
#include "rng_mock.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <boost/range/irange.hpp>

using testing::Eq;
using std::vector;
using boost::irange;

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
    for (const auto& i : irange<int>(2))
    {
        for (const auto& expected_brick : expected_bricks)
            ASSERT_THAT(brick_generator.generate(), Eq(expected_brick));
    }
}