#include "ncurses_colors.h"

#include <cassert>

#include <ncurses.h>

namespace Tetris
{

int NCursesColors::get_ncurses_color(int color_code)
{
    auto it{this->color_to_pair.find(color_code)};
    if (it == this->color_to_pair.end())
    {
        assert(this->color_code_to_ncurses_color.find(color_code)
            != this->color_code_to_ncurses_color.end());
        const int ncurses_color{
            this->color_code_to_ncurses_color.at(color_code)
        };
        ::init_pair(ncurses_color, ncurses_color, COLOR_BLACK);
        it = this->color_to_pair.insert({color_code, ncurses_color}).first;
    }
    return it->second;
}

}