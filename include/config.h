#ifndef INCLUDE_CONFIG
#define INCLUDE_CONFIG

#include <cstdint>
#include <map>
#include <vector>

#include "action.h"
#include "brick.h"
#include "settings.h"

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
    std::vector<uint_fast8_t> color_ids;
    int brick_spawn_position_y;
    Settings default_settings;
};

struct DisplayConfig final
{
    int width;
    int height;
};

struct UiConfig final
{
    DisplayConfig display;
    std::map<int, Action> key_code_to_action;
    uint_fast8_t ghost_color_value;
    uint_fast8_t background_color_id;
    uint_fast8_t border_color_id;
    uint_fast8_t font_color_id;
};

struct ControlsConfig final
{
    int pause_key_code;
    int quit_key_code;
    int no_key_code;
};

struct Config final
{
    GameConfig game;
    UiConfig ui;
    ControlsConfig controls;
};

}

#endif