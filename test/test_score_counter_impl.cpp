#include "score_counter_impl.h"
#include <gtest/gtest.h>

TEST(ScoreCounterImpl, test_count_score_for_lines)
{
    ScoreCounterImpl score_counter{2, 1, 1};
    
    ASSERT_EQ(score_counter.count_score_for_lines(10), 20);
}

TEST(ScoreCounterImpl, test_count_score_for_soft_drop)
{
    ScoreCounterImpl score_counter{1, 3, 1};
    
    ASSERT_EQ(score_counter.count_score_for_soft_drop(), 3);
}

TEST(ScoreCounterImpl, test_count_score_for_hard_drop)
{
    ScoreCounterImpl score_counter{1, 1, 5};
    
    ASSERT_EQ(score_counter.count_score_for_hard_drop(), 5);
}