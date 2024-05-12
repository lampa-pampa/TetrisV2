#ifndef INCLUDE_CONSOLE_GAME_CONTROLLER_IMPL_H
#define INCLUDE_CONSOLE_GAME_CONTROLLER_IMPL_H

#include <functional>

#include <boost/signals2.hpp>

#include "game_controller/game_controller_key_codes.h"
#include "game/game_state.h"
#include "game/game.h"
#include "timer/timer.h"
#include "ui/input_receiver/input_receiver.h"

namespace Tetris
{

class GameController final
{
public:
    GameController(
        Game& game,
        Timer& timer,
        Ui::InputReceiver& input_receiver,
        GameControllerKeyCodes key_codes);

    bool update(unsigned long delta_time);

    void connect_key_press(const std::function<void(int)> &handler)
    {
        key_press_.connect(handler);
    }

private:
    using Signal = boost::signals2::signal<void(int)>;

    const GameControllerKeyCodes key_codes_;
    
    Game& game_;
    Timer& timer_;
    Ui::InputReceiver& input_receiver_;
    Signal key_press_;
    
    void handle_pause_pressed(GameState state);

    void handle_key_press(int key_code, GameState state)
    {
        if (key_code == key_codes_.no_key)
            return;
        if (key_code == key_codes_.pause)
            handle_pause_pressed(state);
        else if (state == GameState::in_progress)
            key_press_(key_code);
    }

    void end_game()
    {
        game_.game_over();
        timer_.stop();
    }

    void pause_game()
    {
        timer_.stop();
        game_.pause();
    }

    void start_game()
    {
        timer_.start();
        game_.resume();
    }
};

}

#endif