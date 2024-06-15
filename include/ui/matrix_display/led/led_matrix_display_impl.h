#ifndef INCLUDE_UI_LED_MATRIX_DISPLAY_IMPL_H
#define INCLUDE_UI_LED_MATRIX_DISPLAY_IMPL_H

#include "ui/matrix_display/matrix_display.h"

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "config/matrix_display/led/config.h"
#include "ui/color/led/rgb_colors.h"
#include "ui/color/nv_color.h"
#include "vector2/vector2.h"

namespace Tetris::Ui
{

class LedMatrixDisplayImpl final: public MatrixDisplay
{
public:
    LedMatrixDisplayImpl(const MatrixDisplayConfig& config);

    ~LedMatrixDisplayImpl()
    {
        matrix_.clearScreen();
    }

    void refresh(const NvColorMatrix& buffer) override;

    Vector2 get_size() const override
    {
        return size_;
    }

private:
    const Vector2 size_;
    const RgbColors rgb_colors_;
    MatrixPanel_I2S_DMA matrix_;

    void refresh_pixel(Vector2 position, NvColor color);
};

} // namespace Tetris::Ui

#endif
