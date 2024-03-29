#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <functional>

namespace Tetris
{

class GameController
{
public:
    virtual void run() = 0;
    virtual void connect_key_press(const std::function<void(int)> &handler) = 0;
    virtual ~GameController() = default;
};

}

#endif