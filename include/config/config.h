#ifndef INCLUDE_CONFIG_H
#define INCLUDE_CONFIG_H

#include <vector>

#include "brick/brick.h"
#include "game/settings.h"
#include "game_controller/game_controller_key_codes.h"
#include "score_counter/score_counter_score_for.h"
#include "ui/color/color_id_name.h"
#include "ui/game_ui/game_ui_colors.h"
#include "ui/game_ui/game_ui_components.h"
#include "ui/game_ui/game_ui_controls.h"
#include "vector_2/vector_2.h"

namespace Tetris
{

struct BoardConfig final
{
    Vector2 size;
    int offset;
};

struct ScoreCounterConfig final
{
    ScoreCounterScoreFor score_for;
};

struct GameConfig final
{
    BoardConfig board;
    ScoreCounterConfig score_counter;
    std::vector<Brick> bricks;
    std::vector<Ui::ColorIdName> color_id_names;
    Settings default_settings;
    Vector2 brick_spawn_position;
    int next_level_lines_quantity;
};

struct UiConfig final
{
    Ui::GameUiControls controls;
    Ui::GameUiComponents components;
    Ui::GameUiColors colors;
    int cube_size;
};

struct GameControllerConfig final
{
    GameControllerKeyCodes key_codes;
};

struct Config final
{
    UiConfig ui;
    GameConfig game;
    GameControllerConfig controller;
};

} // namespace Tetris

#endif
