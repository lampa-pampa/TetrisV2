#ifndef INCLUDE_CONFIG_H
#define INCLUDE_CONFIG_H

#include <cstdint>
#include <map>
#include <vector>

#include "action.h"
#include "brick.h"
#include "settings.h"
#include "vector_2.h"

namespace Tetris
{

struct BoardConfig final
{
    Vector2 size;
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
    Settings default_settings;
    Vector2 brick_spawn_position;
    int next_level_lines_quantity;
};

struct DisplayConfig final
{
    Vector2 size;
    Vector2 pixel_size;
    std::vector<wchar_t> pixel_chars;
    int max_color_value;
};

struct UiConfig final
{
    DisplayConfig display;
    std::map<int, Action> key_code_to_action;
    uint_fast8_t ghost_color_value;
    uint_fast8_t border_color_id;
    uint_fast8_t font_color_id;
    uint_fast8_t empty_level_progress_bar_color_id;
    uint_fast8_t level_progress_bar_color_id;
};

struct GameControllerConfig final
{
    int pause_key_code;
    int quit_key_code;
    int no_key_code;
};

struct Config final
{
    UiConfig ui;
    GameConfig game;
    GameControllerConfig controller;
};

}

#endif