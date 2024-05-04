#ifndef INCLUDE_UI_NCURSES_COLORS_H
#define INCLUDE_UI_NCURSES_COLORS_H

#include <cstdint>
#include <map>

namespace Tetris::Ui
{

class NCursesColors final
{
public:
    NCursesColors(
        const std::map<uint_fast8_t, uint_fast8_t>& color_id_to_ncurses_color)
    :
        color_id_to_ncurses_color_{color_id_to_ncurses_color}
    {}

    int get_ncurses_color(uint_fast8_t color_id);

private:
    using ColorPair = std::_Rb_tree_iterator<
        std::pair<const uint_fast8_t, uint_fast8_t>>;
    
    const std::map<uint_fast8_t, uint_fast8_t> color_id_to_ncurses_color_;
    
    std::map<uint_fast8_t, uint_fast8_t> color_to_pair_;

    ColorPair create_color_pair(uint_fast8_t color_id);
};

}

#endif