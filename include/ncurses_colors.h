#ifndef INCLUDE_NCURSES_COLORS_H
#define INCLUDE_NCURSES_COLORS_H

#include <cassert>
#include <map>

#include <ncurses.h>

namespace Tetris
{

class NCursesColors final
{
public:
    int get_ncurses_color(int color_code)
    {
        auto it{this->color_to_pair.find(color_code)};
        if (it == this->color_to_pair.end())
            it = this->create_color_pair(color_code);
        return it->second;
    }

private:
    using ColorPair = std::_Rb_tree_iterator<std::pair<const int, int>>;
    
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

    ColorPair create_color_pair(int color_code)
    {
        auto it{color_code_to_ncurses_color.find(color_code)};
        assert(it != this->color_code_to_ncurses_color.end());
        ::init_pair(it->second, it->second, COLOR_BLACK);
        return this->color_to_pair.insert({color_code, it->second}).first;
    }
};

}

#endif