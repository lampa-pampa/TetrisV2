#include "bag.h"
#include "rng_mock.h"
#include <gtest/gtest.h>
#include <memory>
#include <vector>

using std::vector;
using std::unique_ptr;

TEST(Bag, get_next)
{
    vector<int> items{0, 1, 2, 3, 4};
    Bag<int> bag{items, unique_ptr<RNG>{new RNGMock{}}};
    for(int i{0}; i < 2; ++i)
    {
        auto it{items.begin()};
        while(it != items.end())
            ASSERT_EQ(bag.get_next(), *it++);
    }
}