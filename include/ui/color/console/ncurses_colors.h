#ifndef INCLUDE_UI_NCURSES_COLORS_H
#define INCLUDE_UI_NCURSES_COLORS_H

#include <cassert>
#include <cstdint>
#include <map>

#include <ncurses.h>

#include "ui/color/color_name.h"

namespace Tetris::Ui
{

class NCursesColors final
{
public:
    NCursesColors(
        const std::map<ColorName, uint_fast8_t>& color_id_to_ncurses_color)
      : color_id_to_ncurses_color_{color_id_to_ncurses_color}
    {}

    void init()
    {
        ::start_color();
        create_color_pairs();
    }

    int get(ColorName color_name) const
    {
        return color_id_to_ncurses_color_.at(color_name);
    }

private:
    const std::map<ColorName, uint_fast8_t> color_id_to_ncurses_color_;

    void create_color_pairs()
    {
        for (const auto& pair : color_id_to_ncurses_color_)
        {
            const int ncurses_color{pair.second};
            ::init_pair(ncurses_color, ncurses_color, COLOR_BLACK);
        }
    }
};

} // namespace Tetris::Ui

#endif
