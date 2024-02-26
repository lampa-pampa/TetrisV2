#include "bag.h"
#include "rng_mock.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

using testing::Eq;
using std::vector;

TEST(Bag, get_next)
{
    RNGMock rng{};
    vector<int> items{0, 1, 2, 3, 4};
    Bag<int> bag{items, rng};
    for(int i{0}; i < 2; ++i)
    {
        auto it{items.begin()};
        while(it != items.end())
            ASSERT_THAT(bag.get_next(), Eq(*it++));
    }
}