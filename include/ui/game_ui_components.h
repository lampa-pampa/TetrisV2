#ifndef INCLUDE_UI_GAME_UI_COMPONENTS_H
#define INCLUDE_UI_GAME_UI_COMPONENTS_H

#include <string>

#include "progress_bar.h"
#include "rectangle.h"
#include "text_area.h"

namespace Tetris::Ui
{

struct ContainerGameUiComponents final
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

struct TextAreaGameUiComponents final
{
    TextArea level_text;
    TextArea level_value;
    TextArea game_state;
    TextArea score_text;
    TextArea score_value;
    TextArea tetrises_text;
    TextArea tetrises_value;
};

struct TextGameUiComponents final
{
    std::string paused;
    std::string game_over;
    std::string level;
    std::string score;
    std::string tetrises;
};

struct ProgressBarComponents final
{
    ProgressBar level;
};

struct GameUiComponents final
{
    ContainerGameUiComponents container;
    TextAreaGameUiComponents text_area;
    TextGameUiComponents text;
    ProgressBarComponents progress_bar;
};

}

#endif