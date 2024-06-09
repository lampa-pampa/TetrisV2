#ifndef INCLUDE_UI_RGB_COLORS_H
#define INCLUDE_UI_RGB_COLORS_H

#include <cstdint>
#include <vector>

#include "ui/color/iv_color.h"
#include "ui/color/led/hs_color.h"
#include "ui/color/led/rgb_color.h"

namespace Tetris::Ui
{

class RgbColors final
{
public:
    using Colors = std::map<uint_fast8_t, std::vector<RgbColor>>;

    RgbColors(const std::map<uint_fast8_t, HsColor>& color_id_to_hs_color,
        int max_color_value)
      : colors_{create_colors(color_id_to_hs_color, max_color_value)}
    {}

    RgbColor get(IvColor iv_color) const
    {
        return colors_.at(iv_color.id).at(iv_color.value);
    }

private:
    const Colors colors_;
    Colors create_colors(
        const std::map<uint_fast8_t, HsColor>& color_id_to_hs_color,
        int max_color_value) const;
};

} // namespace Tetris::Ui

#endif
