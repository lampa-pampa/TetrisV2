#include "ncurses_colors.h"
#include <ncurses.h>
#include"color.h"

namespace Tetris
{

int NCursesColors::get_color_pair(Color color)
{
    auto it = this->color_to_pair.find(color);
    if (it == this->color_to_pair.end())
    {
        const int ncurses_color{this->color_to_ncurses_color.at(color)};
        ::init_pair(ncurses_color, ncurses_color, COLOR_BLACK);
        it = this->color_to_pair.insert({color, ncurses_color}).first;
    }
    return it->second;
}

}