#ifndef UI_FONT
#define UI_FONT

#include "ui/render/text/char.h"
#include "vector2/vector2.h"

#include <initializer_list>
#include <map>
#include <string>
#include <vector>

#include <boost/range/irange.hpp>

namespace Tetris::Ui
{

class Font final
{
public:
    using CharShape = std::vector<std::string>;
    using CharShapes = std::initializer_list<std::pair<char, CharShape>>;

    Font(const CharShapes& char_shapes)
      : height_{get_max_char_height(char_shapes)},
        chars_{create_chars(char_shapes)}
    {}

    int get_height() const
    {
        return height_;
    }

    Char get_char(char c) const
    {
        return chars_.at(c);
    }

private:
    const int height_;
    const std::map<char, Char> chars_;

    int get_max_char_height(const CharShapes& char_shapes) const;
    int get_char_width(const CharShape& c) const;
    std::vector<Vector2> create_char_pixels(const CharShape& char_shape) const;
    std::map<char, Char> create_chars(const CharShapes& char_shapes) const;
};

} // namespace Tetris::Ui

#endif
