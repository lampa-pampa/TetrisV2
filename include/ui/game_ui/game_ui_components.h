#ifndef INCLUDE_UI_GAME_UI_COMPONENTS_H
#define INCLUDE_UI_GAME_UI_COMPONENTS_H

#include <string>

#include "ui/progress_bar/progress_bar.h"
#include "ui/rectangle/rectangle.h"
#include "ui/text_area/text_area.h"

namespace Tetris::Ui
{

struct Containers final
{
    Rectangle hold;
    Rectangle next;
    Rectangle level_text;
    Rectangle level_value;
    Rectangle board;
    Rectangle score_text;
    Rectangle score_value;
    Rectangle tetrises_text;
    Rectangle tetrises_value;
};

struct ValueDisplay final
{
    TextArea label_display;
    std::string label_text;
    TextArea value_display;
    int max_value_length;
};

struct ProgressBarDisplay final
{
    ProgressBar bar;
    ValueDisplay display;
};

struct DisplayGameUiComponents final
{
    TextArea game_state;
    ProgressBarDisplay level;
    ValueDisplay score;
    ValueDisplay tetrises;
};

struct GameUiComponents final
{
    Containers containers;
    DisplayGameUiComponents displays;
};

} // namespace Tetris::Ui

#endif
