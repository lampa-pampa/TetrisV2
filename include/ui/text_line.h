#ifndef INCLUDE_UI_TEXT_LINE_H
#define INCLUDE_UI_TEXT_LINE_H

#include <vector>

#include "char.h"
#include "rectangle.h"
#include "vector_2.h"

namespace Tetris::Ui
{

struct TextLine final
{
    Rectangle background;
    Vector2 position;
    std::vector<Char> chars;
    int color_code;

    TextLine(
        Rectangle background, 
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