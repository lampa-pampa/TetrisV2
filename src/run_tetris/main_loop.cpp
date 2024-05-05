#include "run_tetris/main_loop.h"

#include <chrono>
#include <thread>

#include "game_controller/game_controller.h"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;
using std::this_thread::sleep_for;

namespace Tetris
{

void main_loop(GameController& game_controller)
{
    auto previous_time{system_clock::now()};

    while(true)
    {
        const auto now{system_clock::now()};
        const auto delta_time{duration_cast<milliseconds>(now - previous_time)};
        if(not game_controller.update(delta_time.count()))
            break;
        previous_time = now;
        sleep_for(milliseconds(5));
    }
}

}