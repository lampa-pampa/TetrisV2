#ifndef INCLUDE_SCORE_COUNTER_MOCK_H
#define INCLUDE_SCORE_COUNTER_MOCK_H

#include "score_counter.h"

class ScoreCounterMock final: public ScoreCounter
{
public:
    int count_score_for_lines(int lines) const override
    {
        return 0;
    }

    int count_score_for_soft_drop() const override
    {
        return 0;
    }
    
    int count_score_for_hard_drop(int distance) const override
    {
        return 0;
    }
};

#endif