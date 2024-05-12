#include "ui/color/led/rgb_color.h"

#include <cstdint>

#include "ui/color/led/hs_color.h"


namespace Tetris::Ui
{

constexpr RgbColor RgbColor::from_hsv(HsColor hs_color, uint_fast8_t value)
{
    if (hs_color.saturation == 0)
        return {value, value, value};

    const uint_fast8_t region(hs_color.hue / 43);
    const uint_fast8_t remainder((hs_color.hue - region * 43) * 6);
    
    const uint_fast8_t p = value
        * (0xff - hs_color.saturation) >> 8;
    const uint_fast8_t q = value
        * (0xff - (hs_color.saturation * remainder >> 8)) >> 8;
    const uint_fast8_t t = value
        * (0xff - (hs_color.saturation * (0xff - remainder) >> 8)) >> 8;
    
    switch (region)
    {
        case 0: return {value, t, p};
        case 1: return {q, value, p};
        case 2: return {p, value, t};
        case 3: return {p, q, value};
        case 4: return {t, p, value};
        default: return {value, p, q};
    }
}

}