#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "bag.h"
#include "rng_mock.h"

using boost::irange;
using std::vector;
using testing::Eq;
using Tetris::Bag;
using Tetris::RngMock;

TEST(Bag, get_next)
{
    RngMock rng{};
    vector<int> items{0, 1, 2, 3, 4};
    Bag bag{items, rng};
    for (const auto& i : irange<int>(2))
    {
        auto it{items.begin()};
        while(it != items.end())
            ASSERT_THAT(bag.get_next(), Eq(*it++));
    }
}