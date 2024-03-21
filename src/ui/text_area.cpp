#include "ui/text_area.h"

#include <string>
#include <vector>

#include <boost/range/irange.hpp>

#include "ui/align.h"
#include "ui/char.h"
#include "ui/rectangle.h"
#include "ui/text_line.h"
#include "vector_2.h"

using boost::irange;
using std::string;
using std::tuple;
using std::vector;

namespace Tetris::Ui
{

vector<TextLine> TextArea::create_lines(
    const vector<CharsAndWidth>& lines_chars) const
{
    const int start_y{
        this->compute_lines_position_y(lines_chars.size())
    };
    vector<TextLine> lines{};
    for (const auto& i : irange(lines_chars.size()))
    {
        const auto&[line_chars, line_width]{lines_chars[i]};
        const int y = start_y + i * (Char::height + Char::separator);
        lines.emplace_back(this->create_line(line_chars, line_width, y));
    }
    return lines;
}

//-------------------------------------------------------------------------

std::string TextArea::get_fixed_length_text(std::string text) const
{
    if(this->max_text_length < 0)
        return text;
    if(text.size() > this->max_text_length)
        return std::string(this->max_text_length, this->overflow_char);
    return std::string(
        this->max_text_length - text.size(), this->fill_char
    ) + text;
}

bool TextArea::line_should_be_ended(
    int line_width, int i, std::string text) const
{
    return text[i] == '\n'
        or i == text.size() - 1
        or text[i + 1] != '\n'
            and line_width + get_char(text[i + 1]).width + Char::separator
                > this->container.size.x;
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
        if (this->line_should_be_ended(line_width, i, text))
        {
            lines.push_back(tuple<vector<Char>, int>{line_chars, line_width});
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
    const auto it{this->horizontal_align_to_compute.find(align)};
    assert(it != this->horizontal_align_to_compute.end());
    return it->second(container_size, content_size);
}

int TextArea::compute_lines_position_y(int lines_quantity) const
{
    const int lines_height{this->compute_lines_height(lines_quantity)};
    if (lines_height > this->container.size.y)
        return 0;
    return this->compute_aligned_position(
        this->vertical_align, this->container.size.y, lines_height);
}

int TextArea::compute_line_position_x(int line_width) const
{
    if (line_width > this->container.size.x)
        return 0;
    return this->compute_aligned_position(
        this->horizontal_align, this->container.size.x, line_width);
}

TextLine TextArea::create_line(const vector<Char>& chars, int width, int y) const
{
    const Vector2 line_position{
        this->container.position
            + Vector2{this->compute_line_position_x(width), y}
    };
    return {
        this->create_line_background(line_position, width),
        line_position,
        chars,
    };        
}

}