#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "score_counter_impl.h"

using testing::Eq;
using Tetris::ScoreCounterImpl;

TEST(ScoreCounterImpl, test_count_score_for_lines)
{
    ScoreCounterImpl score_counter{2, 1, 1};
    
    ASSERT_THAT(score_counter.count_score_for_lines(10), Eq(20));
}

TEST(ScoreCounterImpl, test_count_score_for_soft_drop)
{
    ScoreCounterImpl score_counter{1, 3, 1};
    
    ASSERT_THAT(score_counter.count_score_for_soft_drop(), Eq(3));
}

TEST(ScoreCounterImpl, test_count_score_for_hard_drop)
{
    ScoreCounterImpl score_counter{1, 1, 5};
    
    ASSERT_THAT(score_counter.count_score_for_hard_drop(10), Eq(50));
}