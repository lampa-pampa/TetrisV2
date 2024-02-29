#ifndef INCLUDE_NCURSES_COLORS_H
#define INCLUDE_NCURSES_COLORS_H

#include <map>

#include <ncurses.h>

#include "color.h"

namespace Tetris
{

class NCursesColors final
{
    const std::map<Color, int> color_to_ncurses_color
    {
        {Color::black, -1},
        {Color::red, COLOR_RED},
        {Color::green, COLOR_GREEN},
        {Color::yellow, COLOR_YELLOW},
        {Color::blue, COLOR_BLUE},
        {Color::purple, COLOR_MAGENTA},
        {Color::orange, COLOR_CYAN},
        {Color::pink, 9},
    };
    
    std::map<Color, int> color_to_pair;
    
public:
    int get_color_pair(Color color);
};

}

#endif