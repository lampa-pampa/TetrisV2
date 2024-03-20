#ifndef INCLUDE_GAME_CONTROLLER_H
#define INCLUDE_GAME_CONTROLLER_H

#include <functional>

#include <boost/signals2.hpp>
#include <ncurses.h>

#include "game_state.h"
#include "game.h"
#include "timer.h"

namespace Tetris
{

class GameController final
{
public:
    GameController(
        Timer& timer,
        Game& game,
        ::WINDOW * window,
        int pause_key_code,
        int quit_key_code,
        int no_key_code);

    void run();

    void connect_key_press(const std::function<void(int)> &handler)
    {
        this->key_press.connect(handler);
    }

private:
    using Signal = boost::signals2::signal<void(int)>;

    const int pause_key_code;
    const int quit_key_code;
    const int no_key_code;
    
    Timer& timer;
    Game& game;
    ::WINDOW * window;
    Signal key_press;
    
    void handle_pause_pressed();

    void update(int key_code, GameState state)
    {
        this->update_timer();
        this->update_key_press(key_code, state);
    }

    void update_timer()
    {
        if (this->timer.is_active())
            this->timer.update_time();
    }

    void update_key_press(int key_code, GameState state)
    {
        if (key_code == this->pause_key_code)
            this->handle_pause_pressed();
        else if (key_code != this->no_key_code
            and state == GameState::in_progress
        )
            this->key_press(key_code);
    }

    void end_game()
    {
        this->game.game_over();
        this->timer.stop();
    }

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