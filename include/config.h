#ifndef INCLUDE_CONFIG
#define INCLUDE_CONFIG

namespace Tetris
{

struct GameConfig
{
    int tetris_line_count;
    int board_offset;
    int brick_start_position_y;
};

struct Config
{
    GameConfig game_config; 
};

}

#endif