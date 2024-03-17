#include "ui/ncurses_colors.h"

#include <cassert>

#include <ncurses.h>

namespace Tetris::Ui
{

int NCursesColors::get_ncurses_color(int color_code)
{
    auto it{this->color_to_pair.find(color_code)};
    if (it == this->color_to_pair.end())
        it = this->create_color_pair(color_code);
    return it->second;
}

//----------------------------------------------------

NCursesColors::ColorPair NCursesColors::create_color_pair(int color_code)
{
    auto it{color_code_to_ncurses_color.find(color_code)};
    assert(it != this->color_code_to_ncurses_color.end());
    ::init_pair(it->second, it->second, COLOR_BLACK);
    return this->color_to_pair.insert({color_code, it->second}).first;
}

}