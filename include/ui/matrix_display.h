#ifndef INCLUDE_UI_MATRIX_DISPLAY_H
#define INCLUDE_UI_MATRIX_DISPLAY_H

#include <vector>

#include "iv_color.h"

namespace Tetris::Ui
{

class MatrixDisplay
{
public:   
    using IvColorMatrix = std::vector<std::vector<IvColor>>;

    virtual void refresh(const IvColorMatrix& colors) = 0;
    virtual int get_width() const = 0;
    virtual int get_height() const = 0;
    virtual ~MatrixDisplay() = default;
};

}

#endif