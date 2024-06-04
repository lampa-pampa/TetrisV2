#ifndef INCLUDE_UI_GAME_UI_STATE_MESSAGES
#define INCLUDE_UI_GAME_UI_STATE_MESSAGES

#include <string>

namespace Tetris::Ui
{

struct GameUiStateMessages final
{
    std::string paused;
    std::string game_over;
};

} // namespace Tetris::Ui

#endif
