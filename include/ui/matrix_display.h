#ifndef INCLUDE_UI_MATRIX_DISPLAY
#define INCLUDE_UI_MATRIX_DISPLAY

#include <vector>

namespace Tetris::Ui
{

class MatrixDisplay
{
public:   
    using ColorCodeMatrix = std::vector<std::vector<int>>;

    virtual void refresh(const ColorCodeMatrix& color_ids) = 0;
    virtual int get_width() const = 0;
    virtual int get_height() const = 0;
    virtual ~MatrixDisplay() = default;
};

}

#endif