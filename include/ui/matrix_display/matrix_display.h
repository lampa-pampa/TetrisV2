#ifndef INCLUDE_UI_MATRIX_DISPLAY_H
#define INCLUDE_UI_MATRIX_DISPLAY_H

#include <vector>

#include "ui/color/iv_color.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class MatrixDisplay
{
public:   
    using IvColorMatrix = std::vector<std::vector<IvColor>>;

    virtual void refresh(const IvColorMatrix& colors) = 0;
    virtual Vector2 get_size() const = 0;
    virtual ~MatrixDisplay() = default;
};

}

#endif