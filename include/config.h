#ifndef INCLUDE_CONFIG
#define INCLUDE_CONFIG

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
    std::vector<int> color_codes;
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
    int background_color_code;
};

struct ControlsConfig final
{
    int pause_key_code;
    int quit_key_code;
    int no_key_code;
};

struct TimerConfig final
{
    unsigned long long timeout_delay;
};

struct Config final
{
    GameConfig game;
    UiConfig ui;
    ControlsConfig controls;
    TimerConfig timer;
};

}

#endif