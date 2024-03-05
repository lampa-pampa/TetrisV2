#ifndef INCLUDE_CONFIG
#define INCLUDE_CONFIG

namespace Tetris
{

struct GameConfig
{
    int brick_start_position_y;
    bool generate_ghost;
};

struct BoardConfig
{
    int width;
    int height;
    int offset;
};

struct Config
{
    BoardConfig board; 
    GameConfig game;
};

}

#endif