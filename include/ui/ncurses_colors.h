#ifndef INCLUDE_UI_NCURSES_COLORS_H
#define INCLUDE_UI_NCURSES_COLORS_H

#include <cstdint>
#include <map>

namespace Tetris::Ui
{

class NCursesColors final
{
public:
    int get_ncurses_color(uint_fast8_t color_id);

private:
    using ColorPair = std::_Rb_tree_iterator<
        std::pair<const uint_fast8_t, uint_fast8_t>>;
    
    const std::map<uint_fast8_t, uint_fast8_t> color_id_to_ncurses_color
    {
        {0, 16},
        {1, 1},
        {2, 2},
        {3, 3},
        {4, 4},
        {5, 5},
        {6, 6},
        {7, 7},
        {8, 8},
        {9, 9},
        {10, 10},
        {11, 11},
        {12, 12},
        {13, 13},
        {14, 14},
        {15, 15},
    };
    
    std::map<uint_fast8_t, uint_fast8_t> color_to_pair;

    ColorPair create_color_pair(uint_fast8_t color_id);
};

}

#endif