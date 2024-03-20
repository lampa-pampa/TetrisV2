#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

namespace Tetris
{

class GameController
{
public:
    virtual void run() = 0;
    virtual ~GameController() = default;
};

}

#endif