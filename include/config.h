#ifndef INCLUDE_CONFIG
#define INCLUDE_CONFIG

#include <vector>

#include "brick.h"

namespace Tetris
{

struct DisplayConfig
{
    int width;
    int height;
};

struct BoardConfig
{
    int width;
    int height;
    int offset;
};

struct ScoreCounterConfig
{
    int score_for_line;
    int score_for_soft_drop;
    int score_for_hard_drop;
};

struct GameConfig
{
    BoardConfig board;
    ScoreCounterConfig score_counter;
    std::vector<Brick> bricks;
    std::vector<int> color_codes;
    int brick_spawn_position_y;
    bool generate_ghost;
};

struct Config
{
    GameConfig game;
    DisplayConfig display;
};

}

#endif