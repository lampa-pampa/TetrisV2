#include "ui/matrix_display/create_matrix_display_impl.h"

#include <memory>

#include "ui/matrix_display/matrix_display.h"
#include "ui/matrix_display/console/console_matrix_display_impl.h"

using std::shared_ptr;

namespace Tetris::Ui
{

std::shared_ptr<MatrixDisplay> create_matrix_display_impl(
    const MatrixConfig& config)
{
    return shared_ptr<MatrixDisplay>{new ConsoleMatrixDisplayImpl{
        config.size,
        {2, 1},
        0xff,
        {
            L' ',
            L'·',
            L'◦',
            L'◌',
            L'○',
            L'◎',
            L'◉',
            L'●',
        },
        {config.color_id_to_matrix_color}
    }};
}


}