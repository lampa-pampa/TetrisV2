#include "score_counter.h"
#include "score_counter_impl.h"
#include <gtest/gtest.h>
#include <memory>

using std::unique_ptr;

namespace {
    unique_ptr<ScoreCounter> score_counter{new ScoreCounterImpl(1, 1, 1)};
}

TEST(ScoreCounterImpl, test_count_score_for_lines)
{
    ASSERT_EQ(score_counter->count_score_for_lines(10), 10);
}

TEST(ScoreCounterImpl, test_count_score_for_soft_drop)
{
    ASSERT_EQ(score_counter->count_score_for_soft_drop(), 1);
}

TEST(ScoreCounterImpl, test_count_score_for_hard_drop)
{
    ASSERT_EQ(score_counter->count_score_for_hard_drop(), 1);
}