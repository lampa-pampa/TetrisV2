#ifndef INCLUDE_GAME_STATE_H
#define INCLUDE_GAME_STATE_H

#include <map>
#include <ostream>
#include <string>

namespace Tetris
{

enum class GameState
{
    in_progress = 0,
    paused = 1,
    ended = 2,
};

const std::map<GameState, std::string> game_state_to_name
{
    {GameState::in_progress, "in_progress"},
    {GameState::paused, "paused"},
    {GameState::ended, "ended"},
};

inline std::ostream& operator<<(std::ostream& os, GameState state)
{
    return os << "GameState::" << game_state_to_name.at(state);
}

}

#endif