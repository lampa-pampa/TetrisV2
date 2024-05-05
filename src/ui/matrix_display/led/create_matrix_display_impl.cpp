#include "ui/matrix_display/create_matrix_display_impl.h"

#include <memory>

#include "ui/matrix_display/matrix_display.h"
#include "ui/matrix_display/led/led_matrix_display_impl.h"

using std::shared_ptr;

namespace Tetris::Ui
{

std::shared_ptr<MatrixDisplay> create_matrix_display_impl(
    const MatrixConfig& config)
{
    return shared_ptr<MatrixDisplay>{new LedMatrixDisplayImpl{
        config.size,
        160,
        1,
        {
            25,
            26,
            27,
            14,
            12,
            13,
            23,
            19,
            5,
            17,
            33,
            4,
            18,
            16,
        },
        {config.color_id_to_matrix_color}
    }};
}


}