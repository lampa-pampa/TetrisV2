#ifndef INCLUDE_UI_GAME_UI_COLORS
#define INCLUDE_UI_GAME_UI_COLORS

#include <cstdint>

#include "ui/color/iv_color.h"

namespace Tetris::Ui
{

struct ProgressBarIvColors final
{
    IvColor on;
    IvColor off;
};

struct TextIvColors final
{
    IvColor foreground;
    IvColor background;
};

struct DescribedValueColors final
{
    TextIvColors text;
    TextIvColors value;
};

struct IvColors final
{
    IvColor background;
    IvColor border;
    TextIvColors game_state;
    ProgressBarIvColors progress_bar;
    DescribedValueColors level;
    DescribedValueColors score;
    DescribedValueColors tetrises;
};

struct BrickValueColors final
{
    uint_fast8_t hold;
    uint_fast8_t next;
    uint_fast8_t cur;
    uint_fast8_t ghost;
};

struct ValueColors final
{
    uint_fast8_t board;
    BrickValueColors brick;
};

struct GameUiColors final
{
    IvColors iv;
    ValueColors value;
};

} // namespace Tetris::Ui

#endif
