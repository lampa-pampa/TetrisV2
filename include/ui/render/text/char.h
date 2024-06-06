#ifndef INCLUDE_UI_CHAR_H
#define INCLUDE_UI_CHAR_H

#include <vector>

#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

struct Char final
{
    int width;
    std::vector<Vector2> pixels;
};

} // namespace Tetris::Ui

#endif
