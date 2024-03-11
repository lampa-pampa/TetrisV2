#include "brick_generator_impl.h"

#include <utility>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "brick.h"
#include "rng_mock.h"

using boost::irange;
using std::pair;
using std::vector;
using testing::Eq;
using Tetris::Brick;
using Tetris::BrickGeneratorImpl;
using Tetris::RngMock;

TEST(BrickGeneratorImpl, generate)
{
    RngMock initial_rng{};
    const vector<pair<BrickGeneratorImpl, vector<Brick>>> gen_to_expected{
        { {
            { { {{ {1, 0}, {0, 1} }}, {{ {2, 0}, {0, 2} }} }, initial_rng },
            { {1, 3}, initial_rng }
        }, {
            {{ {1, 0, 1}, {0, 1, 1} }},
            {{ {2, 0, 3}, {0, 2, 3} }},
        }},
        { {
            { { {{ {0, 0} }}, {{ {1, 1} }} }, initial_rng },
            { {2, 5}, initial_rng }
        }, {
            {{ {0, 0, 2} }},
            {{ {1, 1, 5} }},
        }},
        { {
            { { {{ {0, 0} }}, {{ {1, 1} }}, {{ {0, 2} }} }, initial_rng },
            { {7}, initial_rng }
        }, {
            {{ {0, 0, 7} }},
            {{ {1, 1, 7} }},
            {{ {0, 2, 7} }},
        }},
    };

    for (const auto& pair : gen_to_expected)
    {
        BrickGeneratorImpl brick_generator{pair.first};
        for (const auto& i : irange(2))
        {
            for (const auto& expected : pair.second)
                ASSERT_THAT(brick_generator.generate(), Eq(expected));
        }
    }
        
}