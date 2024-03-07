#include "bag.h"

#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "rng_mock.h"

using boost::irange;
using std::vector;
using testing::Eq;
using Tetris::Bag;
using Tetris::RngMock;

TEST(Bag, get_next)
{
    RngMock rng{};
    const vector<int> items{ 0, 1, 2, 3, 4 };
    Bag bag{items, rng};
    for (const auto& i : irange(2))
    {
        for (const auto& item : items)
            ASSERT_THAT(bag.get_next(), Eq(item));
    }
}