#ifndef INCLUDE_UI_TEXT_AREA_H
#define INCLUDE_UI_TEXT_AREA_H

#include <functional>
#include <map>
#include <string>
#include <vector>

#include <boost/range/irange.hpp>

#include "ui_char.h"
#include "ui_rectangle.h"
#include "ui_text_line.h"
#include "vector_2.h"

namespace Tetris
{

enum class Align
{
    left,
    center,
    right,
};

class UiTextArea final
{
public:
    UiTextArea(
        Vector2 position, 
        int width,
        int color_code,
        int char_background_margin,
        Align align)
    :
        position{position},
        width{width},
        color_code{color_code},
        char_background_margin{char_background_margin},
        align{align}
    {}

    UiTextArea(
        Vector2 position, 
        int width,
        int color_code,
        int char_background_margin)
    :
        UiTextArea(
            position, width, color_code, char_background_margin, Align::left)
    {}

    UiTextArea(Vector2 position, int width, int color_code)
    :
        UiTextArea(position, width, color_code, 0, Align::left)
    {}

    std::vector<UiTextLine> create_lines(std::string text) const
    {
        std::vector<UiTextLine> lines{};
        int i{0};
        for(int row{0}; i < text.size(); ++row)
        {
            const int line_length{
                this->compute_max_substr_length(i, text.size())
            };
            lines.emplace_back(
                this->create_line(text.substr(i, line_length), row));
            i += line_length;
        }
        return lines;
    }

private:
    Vector2 position;
    int width;
    int color_code;
    int char_background_margin;
    Align align;

    const inline static std::map<Align, std::function<int(int, int)>> 
        align_to_compute
    {
        {Align::left, [](int container_width, int content_width){
            return 0;
        }},
        {Align::center, [](int container_width, int content_width){
            return container_width / 2 - content_width / 2;
        }},
        {Align::right, [](int container_width, int content_width){
            return container_width - content_width;
        }}, 
    };

    int compute_max_substr_length(int index, int text_length) const
    {
        const int max_line_length{UiChar::get_max_text_length(this->width)};
        return (text_length - index >= max_line_length) ?
            max_line_length : text_length - index;
    }

    UiRectangle create_line_background(Vector2 position, int length) const
    {
        return {
            position - this->char_background_margin,
            UiChar::get_text_width(length) + 2 * this->char_background_margin,
            UiChar::height + 2 * this->char_background_margin
        };
    }

    int compute_line_position_x(int length) const
    {
        return (align_to_compute.at(this->align)(
            this->width, UiChar::get_text_width(length)));
    }

    Vector2 compute_line_position(int length, int row) const
    {
        return this->position + Vector2{
            this->compute_line_position_x(length),
            row * (UiChar::height + UiChar::separator)
        };
    }

    UiTextLine create_line(std::string text, int row) const
    {
        const Vector2 text_position{
            this->compute_line_position(text.size(), row)
        };
        return {
            this->create_line_background(text_position, text.size()),
            text_position,
            text,
            this->color_code
        };        
    }
};

}

#endif