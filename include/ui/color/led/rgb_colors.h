#ifndef INCLUDE_UI_RGB_COLORS_H
#define INCLUDE_UI_RGB_COLORS_H

#include <vector>

#include "ui/color/color_name.h"
#include "ui/color/led/hs_color.h"
#include "ui/color/led/rgb_color.h"
#include "ui/color/nv_color.h"

namespace Tetris::Ui
{

class RgbColors final
{
public:
    using Colors = std::map<ColorName, std::vector<RgbColor>>;

    RgbColors(const std::map<ColorName, HsColor>& color_name_to_hs_color,
        int max_color_value)
      : colors_{create_colors(color_name_to_hs_color, max_color_value)}
    {}

    RgbColor get(NvColor iv_color) const
    {
        return colors_.at(iv_color.name).at(iv_color.value);
    }

private:
    const Colors colors_;
    Colors create_colors(
        const std::map<ColorName, HsColor>& color_name_to_hs_color,
        int max_color_value) const;
};

} // namespace Tetris::Ui

#endif
