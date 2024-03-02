#ifndef INCLUDE_MATRIX_DISPLAY
#define INCLUDE_MATRIX_DISPLAY

#include <vector>

namespace Tetris
{

class MatrixDisplay
{
    using ColorCodes = std::vector<std::vector<int>>;

public:   
    virtual void refresh(const ColorCodes& color_codes) = 0;
    virtual int get_width() const = 0;
    virtual int get_height() const = 0;
    virtual ~MatrixDisplay() = default;
};

}

#endif