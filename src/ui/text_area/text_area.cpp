#include "ui/text_area/text_area.h"

#include <string>
#include <vector>

#include <boost/range/irange.hpp>

#include "ui/rectangle/rectangle.h"
#include "ui/text_area/align.h"
#include "ui/text_area/char.h"
#include "ui/text_area/text_line.h"
#include "vector_2/vector_2.h"

using boost::irange;
using std::string;
using std::vector;

namespace Tetris::Ui
{

vector<TextLine> TextArea::create_lines(
    const vector<CharsAndWidth>& lines_chars) const
{
    const int start_y{compute_lines_position_y(lines_chars.size())};
    vector<TextLine> lines{};
    for (const auto& i : irange(lines_chars.size()))
    {
        const auto&[line_chars, line_width]{lines_chars[i]};
        const int y = start_y + i * (Char::height + Char::separator);
        lines.emplace_back(create_line(line_chars, line_width, y));
    }
    return lines;
}

//-------------------------------------------------------------------------

string TextArea::get_fixed_length_text(string text) const
{
    if (max_text_length_ < 0)
        return text;
    if (text.size() > max_text_length_)
        return string(max_text_length_, overflow_char_);
    return string(max_text_length_ - text.size(), fill_char_) + text;
}

bool TextArea::line_should_be_ended(
    int line_width, int i, string text) const
{
    return text[i] == '\n'
        or i == text.size() - 1
        or text[i + 1] != '\n'
            and line_width + get_char(text[i + 1]).width + Char::separator
                > container_.size.x;
}

vector<TextArea::CharsAndWidth> TextArea::slice_text_into_lines(
    string text) const
{
    vector<CharsAndWidth> lines{};
    vector<Char> line_chars{};
    int line_width{};
    for (const auto& i : irange(text.size()))
    {
        if (text[i] != '\n')
        {
            const Char chr{get_char(text[i])};
            line_width += chr.width;
            line_chars.emplace_back(std::move(chr));
            if (line_chars.size() > 1)
                line_width += Char::separator;
        }
        if (line_should_be_ended(line_width, i, text))
        {
            lines.emplace_back(CharsAndWidth{line_chars, line_width});
            line_chars.clear();
            line_width = 0;
        }
    }
    return lines;
}

Rectangle TextArea::create_line_background(Vector2 position, int width) const
{
    return {
        position - Char::separator,
        Vector2{width, Char::height} + 2 * Char::separator
    };
}

int TextArea::compute_aligned_position(
    Align align, int container_size, int content_size) const
{
    const auto it{horizontal_align_to_compute.find(align)};
    assert(it != horizontal_align_to_compute.end());
    return it->second(container_size, content_size);
}

int TextArea::compute_lines_position_y(int lines_quantity) const
{
    const int lines_height{compute_lines_height(lines_quantity)};
    if (lines_height > container_.size.y)
        return 0;
    return compute_aligned_position(
        vertical_align_, container_.size.y, lines_height);
}

int TextArea::compute_line_position_x(int line_width) const
{
    if (line_width > container_.size.x)
        return 0;
    return compute_aligned_position(
        horizontal_align_, container_.size.x, line_width);
}

TextLine TextArea::create_line(const vector<Char>& chars, int width, int y) const
{
    const Vector2 line_position{
        container_.position + Vector2{compute_line_position_x(width), y}
    };
    return {
        create_line_background(line_position, width),
        line_position,
        chars,
    };        
}

}