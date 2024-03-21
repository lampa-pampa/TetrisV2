#ifndef INCLUDE_UI_GAME_UI_COLORS
#define INCLUDE_UI_GAME_UI_COLORS

#include <cstdint>

namespace Tetris::Ui
{

struct ProgressBarGameUiColors final
{
    uint_fast8_t on;
    uint_fast8_t off;
};

struct IdGameUiColors final
{
    uint_fast8_t border;
    uint_fast8_t font;
    ProgressBarGameUiColors progress_bar;
};

struct ValueGameUiColors final
{
    uint_fast8_t ghost_brick;
};

struct GameUiColors final
{
    IdGameUiColors id;
    ValueGameUiColors value;
};

}

#endif