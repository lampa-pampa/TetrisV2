#include "score_counter_impl.h"

namespace Tetris
{

ScoreCounterImpl::ScoreCounterImpl(
    int score_for_line,
    int score_for_soft_drop,
    int score_for_hard_drop)
:
    score_for_line{score_for_line},
    score_for_soft_drop{score_for_soft_drop},
    score_for_hard_drop{score_for_hard_drop}
{}

}