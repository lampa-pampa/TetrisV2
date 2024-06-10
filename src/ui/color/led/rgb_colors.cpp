#include "ui/color/led/rgb_colors.h"

#include <map>
#include <vector>

#include <boost/range/irange.hpp>

#include "ui/color/led/hs_color.h"
#include "ui/color/led/rgb_color.h"

using boost::irange;
using std::map;
using std::vector;

namespace Tetris::Ui
{

RgbColors::Colors RgbColors::create_colors(
    const map<ColorName, HsColor>& color_name_to_hs_color,
    int max_color_value) const
{
    Colors colors{};
    for (const auto& pair : color_name_to_hs_color)
    {
        vector<RgbColor> color_value_to_rgb_color;
        for (const auto& value : irange(max_color_value + 1))
            color_value_to_rgb_color.emplace_back(
                RgbColor::from_hsv(pair.second, value));
        colors.emplace(pair.first, color_value_to_rgb_color);
    }
    return colors;
}

} // namespace Tetris::Ui
