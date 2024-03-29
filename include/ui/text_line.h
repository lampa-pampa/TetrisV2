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
};

}

#endif