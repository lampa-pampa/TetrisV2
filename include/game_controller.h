#ifndef INCLUDE_GAME_CONTROLLER_H
#define INCLUDE_GAME_CONTROLLER_H

#include "game_state.h"
#include "game.h"
#include "timer.h"

#include <functional>
#include <map>

namespace Tetris
{

class GameController final
{
public:
    void handle_pause_pressed()
    {
        if (auto it{this->game_state_to_action.find(this->game.get_state())};
                it != this->game_state_to_action.end())
            it->second();
    }

    GameController(Timer& timer, Game& game)
    :
        timer{timer},
        game{game}
    {}

private:
    Timer& timer;
    Game& game;

    const std::map<GameState, std::function<void()>> game_state_to_action
    {
        {GameState::in_progress, [this](){ this->pause_game(); }},
        {GameState::paused, [this](){ this->start_game(); }},
    };

    void pause_game()
    {
        this->timer.stop();
        this->game.pause();
    }

    void start_game()
    {
        this->timer.start();
        this->game.resume();
    }
};

}

#endif