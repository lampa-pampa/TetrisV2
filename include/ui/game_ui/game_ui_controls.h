#ifndef INCLUDE_UI_GAME_UI_CONTROLS
#define INCLUDE_UI_GAME_UI_CONTROLS

namespace Tetris::Ui
{

struct GameUiControls final
{
    int left;
    int right;
    int rotate_clockwise;
    int soft_drop;
    int locking_hard_drop;
    int no_locking_hard_drop;
    int rotate_counter_clockwise;
    int hold;
};

}

#endif