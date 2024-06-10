#ifndef INCLUDE_GAME_STATE_H
#define INCLUDE_GAME_STATE_H

#include <map>
#include <ostream>
#include <string>

namespace Tetris
{

enum class GameState
{
    in_progress,
    paused,
    ended,
};

const std::map<GameState, std::string> game_state_to_text{
    {GameState::in_progress, "in_progress"},
    {GameState::paused, "paused"},
    {GameState::ended, "ended"},
};

inline std::ostream& operator<<(std::ostream& os, GameState state)
{
    return os << "GameState::" << game_state_to_text.at(state);
}

} // namespace Tetris

#endif