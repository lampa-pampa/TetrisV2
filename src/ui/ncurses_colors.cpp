#include "ui/ncurses_colors.h"

#include <cassert>
#include <cstdint>

#include <ncurses.h>

namespace Tetris::Ui
{

int NCursesColors::get_ncurses_color(uint_fast8_t color_id)
{
    auto it{color_to_pair.find(color_id)};
    if (it == color_to_pair.end())
        it = create_color_pair(color_id);
    return it->second;
}

//----------------------------------------------------

NCursesColors::ColorPair NCursesColors::create_color_pair(
    uint_fast8_t color_id)
{
    auto it{color_id_to_ncurses_color.find(color_id)};
    assert(it != color_id_to_ncurses_color.end());
    ::init_pair(it->second, it->second, COLOR_BLACK);
    return color_to_pair.insert({color_id, it->second}).first;
}

}