#ifndef INCLUDE_CONFIG_H
#define INCLUDE_CONFIG_H

#include <vector>

#include "brick/brick.h"
#include "game/settings.h"
#include "game_controller/game_controller_key_codes.h"
#include "score_counter/score_counter_score_for.h"
#include "ui/game_ui/config.h"
#include "vector2/vector2.h"

namespace Tetris
{

struct BoardConfig final
{
    Vector2 size;
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
    Settings default_settings;
    Vector2 brick_spawn_position;
};

struct GameControllerConfig final
{
    GameControllerKeyCodes key_codes;
};

struct Config final
{
    Ui::GameUiConfig ui;
    GameConfig game;
    GameControllerConfig controller;
};

} // namespace Tetris

#endif
