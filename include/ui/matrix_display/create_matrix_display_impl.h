#ifndef INCLUDE_CREATE_MATRIX_DISPLAY_IMPL_H
#define INCLUDE_CREATE_MATRIX_DISPLAY_IMPL_H

#include <memory>

#include "config/config.h"
#include "ui/matrix_display/matrix_display.h"

namespace Tetris::Ui
{

std::shared_ptr<MatrixDisplay> create_matrix_display_impl(
    const MatrixConfig& config);

}

#endif