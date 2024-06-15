#ifndef INCLUDE_UI_GAME_UI_CONFIG_H
#define INCLUDE_UI_GAME_UI_CONFIG_H

#include <map>
#include <string>
#include <vector>

#include "brick/brick_name.h"
#include "ui/color/color_name.h"
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

struct Ghost final
{
    uint_fast8_t color_value;
    bool fill;
};

struct BoardDisplay final
{
    RenderCubes display;
    Ghost ghost;
};

struct GraphicEngine final
{
    MainDisplay main;
    RenderBrickPreview hold;
    LabeledDisplay level;
    RenderProgressBar progress_bar;
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
    std::map<BrickName, ColorName> brick_name_to_color_name;
    StateMessages state_messages;
};

} // namespace Tetris::Ui

#endif
