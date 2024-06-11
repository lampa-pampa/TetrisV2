#ifndef INCLUDE_GAME_STATE_H
#define INCLUDE_GAME_STATE_H

#include <map>
#include <ostream>
#include <string>

namespace Tetris
{

enum class GameState
{
    active,
    paused,
    ended,
};

const std::map<GameState, std::string> game_state_to_text{
    {GameState::active, "active"},
    {GameState::paused, "paused"},
    {GameState::ended, "ended"},
};

inline std::ostream& operator<<(std::ostream& os, GameState state)
{
    return os << "GameState::" << game_state_to_text.at(state);
}

} // namespace Tetris

#endif
