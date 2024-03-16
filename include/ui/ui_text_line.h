#ifndef INCLUDE_UI_TEXT_LINE_H
#define INCLUDE_UI_TEXT_LINE_H

#include <vector>

#include "ui_char.h"
#include "ui_rectangle.h"
#include "vector_2.h"

namespace Tetris
{

struct UiTextLine final
{
    UiRectangle background;
    Vector2 position;
    std::vector<UiChar> chars;
    int color_code;

    UiTextLine(
        UiRectangle background, 
        Vector2 position,
        std::string chars,
        int color_code)
    :
        background{background},
        position{position},
        color_code{color_code}
    {
        for(const auto& c : chars)
            this->chars.emplace_back(get_ui_char(c));
    }
};

}

#endif