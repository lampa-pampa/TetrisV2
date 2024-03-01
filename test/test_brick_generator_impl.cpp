#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bag.h"
#include "brick_generator_impl.h"
#include "brick.h"
#include "color.h"
#include "rng_mock.h"

using boost::irange;
using std::vector;
using testing::Eq;
using Tetris::Bag;
using Tetris::Brick;
using Tetris::BrickGeneratorImpl;
using Tetris::Color;
using Tetris::RngMock;


TEST(BrickGeneratorImpl, generate)
{
    const vector<Brick> bricks{
        {{ {1, 0}, {0, 1} }},
        {{ {2, 0}, {0, 2} }},
    };
    const vector colors{
        Color::red,
        Color::blue,
    };
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{bricks, rng},
        Bag{colors, rng},
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