#ifndef INCLUDE_UI_GAME_UI_COLORS
#define INCLUDE_UI_GAME_UI_COLORS

#include <cstdint>

#include "iv_color.h"

namespace Tetris::Ui
{

struct ProgressBarGameUiColors final
{
    IvColor on;
    IvColor off;
};

struct LevelGameUiColors final
{
    IvColor text;
    IvColor value;
    ProgressBarGameUiColors progress_bar;
};

struct ScoreGameUiColors final
{
    IvColor text;
    IvColor value;
};

struct TetrisesGameUiColors final
{
    IvColor text;
    IvColor value;
};

struct IvGameUiColors final
{
    IvColor background;
    IvColor border;
    IvColor game_state;
    LevelGameUiColors level;
    ScoreGameUiColors score;
    TetrisesGameUiColors tetrises;
};

struct ValueGameUiColors final
{
    uint_fast8_t hold_brick;
    uint_fast8_t next_brick;
    uint_fast8_t board;
    uint_fast8_t bricks;
    uint_fast8_t ghost_brick;
};

struct GameUiColors final
{
    IvGameUiColors iv;
    ValueGameUiColors value;
};

}

#endif