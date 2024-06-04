#ifndef UI_BITMAP_H
#define UI_BITMAP_H

#include <vector>

#include "ui/rectangle/rectangle.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

struct Bitmap final
{
    Rectangle container;
    std::vector<Vector2> pixels;
};

} // namespace Tetris::Ui

#endif
