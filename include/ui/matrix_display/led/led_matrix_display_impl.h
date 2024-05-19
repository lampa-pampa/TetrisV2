#ifndef INCLUDE_UI_LED_MATRIX_DISPLAY_IMPL_H
#define INCLUDE_UI_LED_MATRIX_DISPLAY_IMPL_H

#include "ui/matrix_display/matrix_display.h"

#include <cstdint>
#include <map>

#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

#include "config/matrix_display/led/config.h"
#include "ui/color/iv_color.h"
#include "ui/color/led/hs_color.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class LedMatrixDisplayImpl final: public MatrixDisplay
{  
public:
    LedMatrixDisplayImpl(const MatrixDisplayConfig& config);

    void refresh(const IvColorMatrix& colors) override;

    Vector2 get_size() const override
    {
        return size_;
    }

private:
    const Vector2 size_;
    const std::map<uint_fast8_t, HsColor> color_id_to_hs_color_;
    MatrixPanel_I2S_DMA matrix_;

    void refresh_pixel(Vector2 position, IvColor color);
};

}

#endif