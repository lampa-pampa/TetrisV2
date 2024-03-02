#ifndef INCLUDE_NCURSES_COLORS_H
#define INCLUDE_NCURSES_COLORS_H

#include <map>

#include <ncurses.h>

namespace Tetris
{

class NCursesColors final
{
    const std::map<int, int> color_code_to_ncurses_color
    {
        {0, 16},
        {1, 9},
        {2, 10},
        {3, 27},
        {4, 11},
        {5, 5},
        {6, 3},
        {7, 13},
        {8, 15},
    };
    
    std::map<int, int> color_to_pair;
    
public:
    int get_ncurses_color(int color_code);
};

}

#endif