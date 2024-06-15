#ifndef INCLUDE_UI_MATRIX_DISPLAY_H
#define INCLUDE_UI_MATRIX_DISPLAY_H

#include <vector>

#include "ui/color/nv_color.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class MatrixDisplay
{
public:
    using NvColorMatrix = std::vector<std::vector<NvColor>>;

    virtual void refresh(const NvColorMatrix& buffer) = 0;
    virtual Vector2 get_size() const = 0;
    virtual ~MatrixDisplay() = default;
};

} // namespace Tetris::Ui

#endif
