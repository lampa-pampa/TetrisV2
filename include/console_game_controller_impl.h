#ifndef INCLUDE_CONSOLE_GAME_CONTROLLER_IMPL_H
#define INCLUDE_CONSOLE_GAME_CONTROLLER_IMPL_H

#include "game_controller.h"

#include <functional>

#include <boost/signals2.hpp>
#include <ncurses.h>

#include "game_state.h"
#include "game.h"
#include "timer.h"

namespace Tetris
{

class ConsoleGameControllerImpl final: public GameController
{
public:
    ConsoleGameControllerImpl(
        Timer& timer,
        Game& game,
        ::WINDOW * window,
        int pause_key_code,
        int quit_key_code,
        int no_key_code);

    void run() override;

    void connect_key_press(const std::function<void(int)> &handler) override
    {
        key_press.connect(handler);
    }

private:
    using Signal = boost::signals2::signal<void(int)>;

    const int pause_key_code_;
    const int quit_key_code_;
    const int no_key_code_;
    
    Timer& timer;
    Game& game;
    ::WINDOW * window;
    Signal key_press;
    
    void handle_pause_pressed();

    void update(int key_code, GameState state)
    {
        update_timer();
        update_key_press(key_code, state);
    }

    void update_timer()
    {
        if (timer.is_active())
            timer.update_time();
    }

    void update_key_press(int key_code, GameState state)
    {
        if (key_code == pause_key_code_)
            handle_pause_pressed();
        else if (key_code != no_key_code_
            and state == GameState::in_progress
        )
            key_press(key_code);
    }

    void end_game()
    {
        game.game_over();
        timer.stop();
    }

    void pause_game()
    {
        timer.stop();
        game.pause();
    }

    void start_game()
    {
        timer.start();
        game.resume();
    }
};

}

#endif