#ifndef SCORE_COUNTER_H
#define SCORE_COUNTER_H

class ScoreCounter
{
    public:
        virtual int count_score_for_lines(int lines) const = 0;
        virtual int count_score_for_soft_drop() const = 0;
        virtual int count_score_for_hard_drop() const = 0;
        virtual ~ScoreCounter() = default;
};

#endif