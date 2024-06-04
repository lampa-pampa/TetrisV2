#include "ui/text_area/text_area.h"

#include <algorithm>
#include <string>
#include <vector>
#include "ui/text_area/align.h"

using std::reverse;
using std::string;
using std::vector;

namespace Tetris::Ui
{

vector<Bitmap> TextArea::create_lines(string text) const
{
    const vector<string> splited_text{split(text)};
    vector<Bitmap> lines{};
    for (const auto& text : splited_text)
        lines.emplace_back(create_line(text));
    set_lines_positions(lines);
    return lines;
}

//-----------------------------------------------------------------------

Bitmap TextArea::create_line(const string& text) const
{
    int width{padding_.x};
    vector<Vector2> pixels{};
    for (const auto& c : text)
    {
        const Char chr = font_.get_char(c);
        for (const auto& pixel : chr.pixels)
            pixels.emplace_back(pixel + Vector2{width, padding_.y});
        width += chr.width;
        if (&c != &text.back())
            width += separator_.x;
    }
    width += padding_.x;
    return {{{}, {width, font_.get_height() + 2 * padding_.y}}, pixels};
}

vector<string> TextArea::split(string text) const
{
    const string wrapped_text = wrap(text);
    vector<string> text_lines{};
    size_t delimiter_index{};
    do
    {
        const size_t new_line_index{wrapped_text.find('\n', delimiter_index)};
        text_lines.emplace_back(wrapped_text.substr(
            delimiter_index, new_line_index - delimiter_index));
        delimiter_index = new_line_index + 1;
    }
    while (delimiter_index != 0);
    return text_lines;
}

string TextArea::wrap(const string& text) const
{
    if (wrap_after_ == 0)
        return text;
    string wrapped_text{};
    string input_text{text};
    if (align_ == Align::end)
        reverse(input_text.begin(), input_text.end());
    string parsed_text{put_new_lines(input_text)};
    if (align_ == Align::end)
        reverse(parsed_text.begin(), parsed_text.end());
    return parsed_text;
}

string TextArea::put_new_lines(const string& text) const
{
    int char_count{};
    string output_text{};
    for (const auto& c : text)
    {
        if (char_count == wrap_after_)
        {
            output_text += '\n';
            char_count = 0;
        }
        output_text += c;
        if (c != '\n')
            ++char_count;
        else
            char_count = 0;
    }
    return output_text;
}

void TextArea::set_lines_positions(vector<Bitmap>& lines) const
{
    int y{compute_all_lines_start_y(lines.size())};
    for (auto& line : lines)
    {
        line.container.position = {compute_line_x(line.container.size.x), y};
        y += font_.get_height() + separator_.y;
    }
}

} // namespace Tetris::Ui
