#include "brick/bag.h"

#include <utility>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "rng/rng_mock.h"

using boost::irange;
using std::pair;
using std::vector;
using testing::Eq;
using Tetris::Bag;
using Tetris::RngMock;

TEST(Bag, get_next)
{
    RngMock rng{};
    const vector<pair<vector<int>, vector<int>>> test_cases{
        {{1, 2, 3}, {1, 2, 3}},
        {{45, 54, 34}, {45, 54, 34}},
        {{1, 0, 1}, {1, 0, 1}},
    };

    for (const auto& pair : test_cases)
    {
        Bag bag{pair.first, rng};
        for (const auto& i : irange(2))
        {
            for (const auto& expected : pair.second)
                ASSERT_THAT(bag.get_next(), Eq(expected));
        }
    }
}
