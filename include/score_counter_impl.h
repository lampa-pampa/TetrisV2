#ifndef SCORE_COUNTER_IMPL_H
#define SCORE_COUNTER_IMPL_H

#include "score_counter.h"

class ScoreCounterImpl: public ScoreCounter
{
    int score_for_line;
    int score_for_soft_drop;
    int score_for_hard_drop;

    public:
        ScoreCounterImpl(int score_for_line, int score_for_soft_drop, int score_for_hard_drop);
        int count_score_for_lines(int lines) const override;
        int count_score_for_soft_drop() const override;
        int count_score_for_hard_drop() const override;
};

#endif