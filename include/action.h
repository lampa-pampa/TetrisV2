#ifndef INCLUDE_ACTION_H
#define INCLUDE_ACTION_H

namespace Tetris
{

enum class Action
{
    move_left,
    move_right,
    rotate_clockwise,
    soft_drop,
    locking_hard_drop,
    rotate_counter_clockwise,
    no_locking_hard_drop,
    hold,
    pause,
};

}

#endif