#ifndef INCLUDE_SCORE_COUNTER_IMPL_H
#define INCLUDE_SCORE_COUNTER_IMPL_H

#include "score_counter/score_counter.h"

#include "score_counter/score_counter_score_for.h"

namespace Tetris
{

class ScoreCounterImpl final: public ScoreCounter
{
public:
    ScoreCounterImpl(ScoreCounterScoreFor score_for)
    :
        score_for_{score_for}
    {}

    int count_score_for_lines(int lines) const override
    {
        return score_for_.line * lines;
    }

    int count_score_for_soft_drop() const override
    {
        return score_for_.soft_drop;
    }

    int count_score_for_hard_drop(int distance) const override
    {
        return score_for_.hard_drop * distance;
    }
    
private:
    const ScoreCounterScoreFor score_for_;
};

}

#endif