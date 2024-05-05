#ifndef INCLUDE_MAIN_LOOP_H
#define INCLUDE_MAIN_LOOP_H

#include "game_controller/game_controller.h"
#include <memory>

namespace Tetris
{

void main_loop(std::unique_ptr<GameController> game_controller);

}

#endif