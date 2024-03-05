#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bag.h"
#include "brick_generator_impl.h"
#include "brick.h"
#include "rng_mock.h"

using boost::irange;
using std::vector;
using testing::Eq;
using Tetris::Bag;
using Tetris::Brick;
using Tetris::BrickGeneratorImpl;
using Tetris::RngMock;


TEST(BrickGeneratorImpl, generate)
{
    const vector<Brick> bricks{ {{ {1, 0}, {0, 1} }}, {{ {2, 0}, {0, 2} }} };
    const vector color_codes{ 1, 3 };
    RngMock rng{};
    BrickGeneratorImpl brick_generator{
        Bag{bricks, rng},
        Bag{color_codes, rng}
    };
    const vector<Brick> expected_bricks{
        {{ {1, 0, 1}, {0, 1, 1} }},
        {{ {2, 0, 3}, {0, 2, 3} }}
    };
        
    for (const auto& i : irange(2))
    {
        for (const auto& expected_brick : expected_bricks)
            ASSERT_THAT(brick_generator.generate(), Eq(expected_brick));
    }
}