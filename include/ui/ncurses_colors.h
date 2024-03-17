#ifndef INCLUDE_UI_NCURSES_COLORS_H
#define INCLUDE_UI_NCURSES_COLORS_H

#include <map>

namespace Tetris::Ui
{

class NCursesColors final
{
public:
    int get_ncurses_color(int color_code);

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

    ColorPair create_color_pair(int color_code);
};

}

#endif