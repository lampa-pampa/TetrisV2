#ifndef NCURSES_COLORS_H
#define NCURSES_COLORS_H

#include <map>
#include "color.h"
#include <ncurses.h>

class NCursesColors final
{
    const std::map<Color, int> color_to_ncurses_color
    {
        {Color::black, COLOR_BLACK},
        {Color::red, COLOR_RED},
        {Color::green, COLOR_GREEN},
        {Color::yellow, COLOR_YELLOW},
        {Color::blue, COLOR_BLUE},
        {Color::purple, COLOR_MAGENTA},
        {Color::orange, COLOR_MAGENTA},
        {Color::pink, COLOR_MAGENTA},
    };
    std::map<Color, int> color_to_pair;
    
public:
    int get_color_pair(Color color)
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
};

#endif