#ifndef INCLUDE_UI_GAME_UI_COLORS
#define INCLUDE_UI_GAME_UI_COLORS

#include <cstdint>

#include "ui/color/iv_color.h"

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

struct BrickGameUiColors final
{
    uint_fast8_t hold;
    uint_fast8_t next;
    uint_fast8_t cur;
    uint_fast8_t ghost;
};

struct ValueGameUiColors final
{
    uint_fast8_t board;
    BrickGameUiColors brick;
};

struct GameUiColors final
{
    IvGameUiColors iv;
    ValueGameUiColors value;
};

} // namespace Tetris::Ui

#endif
