#ifndef INCLUDE_UI_GAME_UI_CONFIG_H
#define INCLUDE_UI_GAME_UI_CONFIG_H

#include <string>
#include <vector>

#include "ui/color/nv_color.h"
#include "ui/render/brick_preview/brick_preview.h"
#include "ui/render/cubes/cubes.h"
#include "ui/render/progress_bar/progress_bar.h"
#include "ui/render/rectangle.h"
#include "ui/render/text/text.h"

namespace Tetris::Ui
{

struct Controls final
{
    int left;
    int right;
    int rotate_clockwise;
    int soft_drop;
    int locking_hard_drop;
    int no_locking_hard_drop;
    int rotate_counter_clockwise;
    int hold;
};

struct MainDisplay final
{
    NvColor bg_color;
    NvColor border_color;
    std::vector<Rectangle> border;
    RenderText display;
};

struct Label final
{
    std::string text;
    RenderText display;
};

struct Value final
{
    int max_length;
    RenderText display;
};

struct LabeledDisplay final
{
    Label label;
    Value value;
};

struct ProgressBarDisplay final
{
    LabeledDisplay display;
    RenderProgressBar progress_bar;
};

struct BoardDisplay final
{
    RenderCubes display;
    uint_fast8_t ghost_color_value;
};

struct GraphicEngine final
{
    MainDisplay main;
    RenderBrickPreview hold;
    ProgressBarDisplay level;
    BoardDisplay board;
    RenderBrickPreview next;
    LabeledDisplay score;
};

struct StateMessages final
{
    std::string paused;
    std::string game_over;
};

struct GameUiConfig final
{
    Controls controls;
    GraphicEngine graphic_engine;
    StateMessages state_messages;
};

} // namespace Tetris::Ui

#endif
