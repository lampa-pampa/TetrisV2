#ifndef INCLUDE_ACTION_H
#define INCLUDE_ACTION_H

#include <map>
#include <ostream>
#include <string>

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
};

namespace
{
    const std::map<Action, std::string> action_to_name
    {
        {Action::move_left, "move_left"},
        {Action::move_right, "paused"},
        {Action::rotate_clockwise, "rotate_clockwise"},
        {Action::soft_drop, "soft_drop"},
        {Action::locking_hard_drop, "locking_hard_drop"},
        {Action::rotate_counter_clockwise, "rotate_counter_clockwise"},
        {Action::no_locking_hard_drop, "no_locking_hard_drop"},
        {Action::hold, "hold"},
    };
}

inline std::ostream& operator<<(std::ostream& os, Action action)
{
    return os << "Action::" << action_to_name.at(action);
}

}

#endif