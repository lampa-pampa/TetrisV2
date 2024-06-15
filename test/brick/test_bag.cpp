#include <utility>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "brick/bag.h"
#include "brick/brick.h"
#include "brick/brick_name.h"
#include "rng/rng_mock.h"

using boost::irange;
using std::pair;
using std::vector;
using testing::Eq;
using Tetris::Bag;
using Tetris::Brick;
using Tetris::BrickName;
using Tetris::RngMock;

TEST(BrickGeneratorImpl, bag)
{
    RngMock initial_rng{};
    const vector<pair<Bag<Brick>, vector<Brick>>> bag_to_expected{
        {
            {
                {
                    {
                        {{{1, 0}, {0, 1}}, BrickName::I},
                        {{{2, 0}, {0, 2}}, BrickName::O},
                    },
                    initial_rng,
                },
                {
                    {{{1, 0}, {0, 1}}, BrickName::I},
                    {{{2, 0}, {0, 2}}, BrickName::O},
                },
            },
        },
    };

    for (const auto& pair : bag_to_expected)
    {
        Bag<Brick> bricks_bag{pair.first};
        for (const auto& i : irange(2))
        {
            for (const auto& expected : pair.second)
                ASSERT_THAT(bricks_bag.get_next(), Eq(expected));
        }
    }
}
