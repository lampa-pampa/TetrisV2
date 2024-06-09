#include "ui/color/console/ncurses_colors.h"

#include <cstdint>

#include <ncurses.h>

namespace Tetris::Ui
{

int NCursesColors::get(uint_fast8_t color_id)
{
    auto it{color_id_to_ncurses_color_.find(color_id)};
    if (it == color_id_to_ncurses_color_.end())
        it = create_color_pair(color_id);
    return it->second;
}

//----------------------------------------------------

NCursesColors::ColorPair NCursesColors::create_color_pair(uint_fast8_t color_id)
{
    const int pair_id{color_id_to_ncurses_id_.at(color_id)};
    ::init_pair(pair_id, pair_id, COLOR_BLACK);
    return color_id_to_ncurses_color_.insert({color_id, pair_id}).first;
}

} // namespace Tetris::Ui
