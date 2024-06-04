#include "ui/text_area/font/font.h"

#include <algorithm>
#include <map>
#include <vector>

using std::map;
using std::max_element;
using std::vector;

namespace Tetris::Ui
{
int Font::get_max_char_height(const CharShapes& char_shapes) const
{
    return max_element(char_shapes.begin(),
        char_shapes.end(),
        [](const auto& a, const auto& b)
        { return a.second.size() < b.second.size(); })
        ->second.size();
}

int Font::get_char_width(const CharShape& c) const
{
    return max_element(c.begin(),
        c.end(),
        [](const auto& a, const auto& b) { return a.size() < b.size(); })
        ->size();
}

vector<Vector2> Font::create_char_pixels(const CharShape& char_shape) const
{
    vector<Vector2> char_pixels{};
    for (const auto& y : boost::irange(char_shape.size()))
    {
        for (const auto& x : boost::irange(char_shape[y].size()))
            if (char_shape[y][x] != ' ')
                char_pixels.emplace_back(x, y);
    }
    return char_pixels;
}

map<char, Char> Font::create_chars(const CharShapes& char_shapes) const
{
    map<char, Char> chars_pixels{};
    for (const auto& [chr, char_shape] : char_shapes)
    {
        chars_pixels.emplace(chr,
            Char{get_char_width(char_shape), create_char_pixels(char_shape)});
    }
    return chars_pixels;
}

} // namespace Tetris::Ui
