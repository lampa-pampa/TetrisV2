#include "ui/render/text/text.h"

#include <algorithm>
#include <string>
#include <vector>

#include "ui/render/container/container.h"
#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"
#include "ui/render/text/align.h"

using std::max_element;
using std::reverse;
using std::string;
using std::to_string;
using std::vector;

namespace Tetris::Ui
{

RenderText::RenderText(const Rectangle& container,
    RenderContainer render_container,
    const Font& font,
    IvColor font_color,
    Align align,
    int wrap_after,
    Vector2 separator,
    bool fill_background)
  : container_{container},
    render_container_{render_container},
    font_{font},
    font_color_{font_color},
    align_{align},
    wrap_after_{wrap_after},
    separator_{separator},
    fill_background_{fill_background}
{}

Sprites RenderText::render(string text) const
{
    TextLines lines{create_lines(text)};
    const int all_lines_height{compute_all_lines_height(lines.size())};
    const int start_y{compute_all_lines_start_y(all_lines_height)};
    set_lines_positions(lines, start_y);
    const Rectangle text_container{
        create_text_container(lines, start_y, all_lines_height)};
    return transform_to_sprites(lines, text_container);
}

Sprites RenderText::render(unsigned long long number, int max_length) const
{
    if (const string text{to_string(number)}; text.size() <= max_length)
        return render(text);
    else
        return render(string(max_length, '9'));
}

//-----------------------------------------------------------------------

RenderText::TextLines RenderText::create_lines(const string& text) const
{
    const vector<string> splited_text{split(text)};
    TextLines lines{};
    for (const auto& line_text : splited_text)
        lines.emplace_back(create_line(line_text));
    return lines;
}

TextLine RenderText::create_line(const string& text) const
{
    int width{};
    vector<Vector2> pixels{};
    for (const auto& c : text)
    {
        const Char chr = font_.get_char(c);
        for (const auto& pixel : chr.pixels)
            pixels.emplace_back(pixel + Vector2{width, 0});
        width += chr.width;
        if (&c != &text.back())
            width += separator_.x;
    }
    return {{}, width, pixels};
}

vector<string> RenderText::split(string text) const
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

string RenderText::wrap(const string& text) const
{
    if (wrap_after_ == 0)
        return text;
    string wrapped_text{};
    string input_text{text};
    if (align_ == Align::end)
        reverse(input_text.begin(), input_text.end());
    string parsed_text{put_line_breaks(input_text)};
    if (align_ == Align::end)
        reverse(parsed_text.begin(), parsed_text.end());
    return parsed_text;
}

string RenderText::put_line_breaks(const string& text) const
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

void RenderText::set_lines_positions(TextLines& lines, int start_y) const
{
    int y{start_y};
    for (auto& line : lines)
    {
        line.position = {compute_line_x(line.width), y};
        y += font_.get_height() + separator_.y;
    }
}

Rectangle RenderText::create_text_container(
    const TextLines& lines, int start_y, int all_lines_height) const
{
    const auto longest_line{max_element(lines.begin(),
        lines.end(),
        [](const auto& a, const auto& b) { return a.width < b.width; })};
    return {
        {longest_line->position.x, start_y},
        {longest_line->width, all_lines_height},
    };
}

Sprites RenderText::transform_to_sprites(
    const TextLines& lines, const Rectangle& text_container) const
{
    Sprites sprites{render_container_.render(
        fill_background_ ? container_ : text_container)};
    for (const auto& line : lines)
        sprites.emplace_back(line.position, line.text, font_color_);
    return sprites;
}

} // namespace Tetris::Ui
