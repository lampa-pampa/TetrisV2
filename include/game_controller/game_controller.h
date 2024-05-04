#ifndef INCLUDE_CONSOLE_GAME_CONTROLLER_IMPL_H
#define INCLUDE_CONSOLE_GAME_CONTROLLER_IMPL_H

#include <functional>

#include <boost/signals2.hpp>
#include <ncurses.h>

#include "game_controller/game_controller_key_codes.h"
#include "game/game_state.h"
#include "game/game.h"
#include "timer/timer.h"

namespace Tetris
{

class GameController final
{
public:
    GameController(
        Timer& timer,
        Game& game,
        ::WINDOW * window,
        GameControllerKeyCodes key_codes);

    void run();

    void connect_key_press(const std::function<void(int)> &handler)
    {
        key_press_.connect(handler);
    }

private:
    using Signal = boost::signals2::signal<void(int)>;

    const GameControllerKeyCodes key_codes_;
    
    Timer& timer_;
    Game& game_;
    ::WINDOW * window_;
    Signal key_press_;
    
    void handle_pause_pressed();

    void update(int key_code, GameState state)
    {
        update_timer();
        update_key_press(key_code, state);
    }

    void update_timer()
    {
        if (timer_.is_active())
            timer_.update_time();
    }

    void update_key_press(int key_code, GameState state)
    {
        if (key_code == key_codes_.pause)
            handle_pause_pressed();
        else if (key_code != key_codes_.no_key
            and state == GameState::in_progress
        )
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