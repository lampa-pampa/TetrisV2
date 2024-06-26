#include "score_counter/score_counter_impl.h"

#include <utility>
#include <vector>

#include <boost/range/irange.hpp>
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using boost::irange;
using std::pair;
using std::vector;
using testing::Eq;
using Tetris::ScoreCounterImpl;

TEST(ScoreCounterImpl, test_count_score_for_lines)
{
    const vector<pair<ScoreCounterImpl, int>> test_cases{
        {{{2, 2, 1}}, 2},
        {{{10, 7, 3}}, 10},
        {{{15, 9, 2}}, 15},
    };

    for (const auto& pair : test_cases)
    {
        for (const auto& lines_count : irange(3))
        {
            const int actual{pair.first.count_score_for_lines(lines_count)};

            ASSERT_THAT(actual, Eq(pair.second * lines_count));
        }
    }
}

TEST(ScoreCounterImpl, test_count_score_for_soft_drop)
{
    const vector<pair<ScoreCounterImpl, int>> test_cases{
        {{{2, 2, 1}}, 1},
        {{{10, 7, 3}}, 3},
        {{{15, 9, 2}}, 2},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first.count_score_for_soft_drop(), Eq(pair.second));
}

TEST(ScoreCounterImpl, test_count_score_for_hard_drop)
{
    const vector<pair<ScoreCounterImpl, int>> test_cases{
        {{{2, 2, 1}}, 2},
        {{{10, 7, 3}}, 7},
        {{{15, 9, 2}}, 9},
    };

    for (const auto& pair : test_cases)
    {
        for (const auto& distance : irange(10))
        {
            const int actual{pair.first.count_score_for_hard_drop(distance)};

            ASSERT_THAT(actual, Eq(pair.second * distance));
        }
    }
}
