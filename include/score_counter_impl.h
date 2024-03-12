#ifndef INCLUDE_SCORE_COUNTER_IMPL_H
#define INCLUDE_SCORE_COUNTER_IMPL_H

#include "score_counter.h"

namespace Tetris
{

class ScoreCounterImpl final: public ScoreCounter
{
public:
    ScoreCounterImpl(
        int score_for_line,
        int score_for_soft_drop,
        int score_for_hard_drop);

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
    
private:
    int score_for_line;
    int score_for_soft_drop;
    int score_for_hard_drop;
};

}

#endif