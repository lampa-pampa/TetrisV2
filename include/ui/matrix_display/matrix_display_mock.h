
#ifndef INCLUDE_UI_MATRIX_DISPLAY_MOCK_H
#define INCLUDE_UI_MATRIX_DISPLAY_MOCK_H

#include "ui/matrix_display/matrix_display.h"

#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class MatrixDisplayMock final: public MatrixDisplay
{
public:
    MatrixDisplayMock(const Vector2& position): size_{position}, buffer_{} {};

    void refresh(const NvColorMatrix& buffer) override
    {
        buffer_ = buffer;
    }

    Vector2 get_size() const override
    {
        return size_;
    }

    NvColorMatrix get_buffer() const
    {
        return buffer_;
    }

private:
    const Vector2 size_;
    NvColorMatrix buffer_;
};

} // namespace Tetris::Ui

#endif
