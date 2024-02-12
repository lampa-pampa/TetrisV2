#include "score_counter_impl.h"

ScoreCounterImpl::ScoreCounterImpl(int score_for_line, int score_for_soft_drop, int score_for_hard_drop)
:
    score_for_line(score_for_line),
    score_for_soft_drop(score_for_soft_drop),
    score_for_hard_drop(score_for_hard_drop)
{}

int ScoreCounterImpl::count_score_for_lines(int lines) const
{
    return this->score_for_line * lines;
}

int ScoreCounterImpl::count_score_for_soft_drop() const
{
    return this->score_for_soft_drop;
}

int ScoreCounterImpl::count_score_for_hard_drop() const
{
    return this->score_for_hard_drop;
}