#ifndef INCLUDE_CONFIG
#define INCLUDE_CONFIG

#include <vector>

#include "brick.h"

namespace Tetris
{

struct BoardConfig final
{
    int width;
    int height;
    int offset;
};

struct ScoreCounterConfig final
{
    int score_for_line;
    int score_for_soft_drop;
    int score_for_hard_drop;
};

struct GameConfig final
{
    BoardConfig board;
    ScoreCounterConfig score_counter;
    std::vector<Brick> bricks;
    std::vector<int> color_codes;
    int brick_spawn_position_y;
    bool generate_ghost;
};

struct DisplayConfig final
{
    int width;
    int height;
};

struct UiConfig final
{
    DisplayConfig display;
    int background_color_code;
};

struct Config final
{
    GameConfig game;
    UiConfig ui;
};

}

#endif