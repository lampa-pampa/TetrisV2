#ifndef SCORE_COUNTER_IMPL_H
#define SCORE_COUNTER_IMPL_H

#include "score_counter.h"

class ScoreCounterImpl final: public ScoreCounter
{
    int score_for_line;
    int score_for_soft_drop;
    int score_for_hard_drop;

    public:
        ScoreCounterImpl(int score_for_line, int score_for_soft_drop, int score_for_hard_drop)
        :
            score_for_line(score_for_line),
            score_for_soft_drop(score_for_soft_drop),
            score_for_hard_drop(score_for_hard_drop)
        {}

        int count_score_for_lines(int lines) const override
        {
            return this->score_for_line * lines;
        }

        int count_score_for_soft_drop() const override
        {
            return this->score_for_soft_drop;
        }

        int count_score_for_hard_drop(int distance) const override
        {
            return this->score_for_hard_drop * distance;
        }
};

#endif