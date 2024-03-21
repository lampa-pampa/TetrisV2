#ifndef INCLUDE_UI_TEXT_AREA_H
#define INCLUDE_UI_TEXT_AREA_H

#include <functional>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "align.h"
#include "char.h"
#include "rectangle.h"
#include "text_line.h"
#include "vector_2.h"

namespace Tetris::Ui
{

class TextArea final
{
public:
    constexpr TextArea(
        const Rectangle& container, 
        int max_text_length = -1,
        char fill_char = ' ',
        char overflow_char = '9',
        Align horizontal_align = Align::center,
        Align vertical_align = Align::center)
    :
        container{container},
        horizontal_align{horizontal_align},
        vertical_align{vertical_align},
        max_text_length{max_text_length},
        fill_char{fill_char},
        overflow_char{overflow_char}
    {}

    std::vector<TextLine> create_lines(std::string text) const
    {
        return this->create_lines(
            this->slice_text_into_lines(this->get_fixed_length_text(text)));
    }

private:
    using AlignToFuncion = std::map<Align, std::function<int(int, int)>>;
    using CharsAndWidth = std::tuple<std::vector<Char>, int>;

    const Rectangle container;
    const Align horizontal_align;
    const Align vertical_align;
    const int max_text_length;
    const char fill_char;
    const char overflow_char;

    const inline static AlignToFuncion horizontal_align_to_compute
    {
        {Align::start, [](int container_size, int content_size){
            return 0;
        }},
        {Align::center, [](int container_size, int content_size){
            return container_size / 2 - content_size / 2;
        }},
        {Align::end, [](int container_size, int content_size){
            return container_size - content_size;
        }},
    };

    std::string get_fixed_length_text(std::string text) const;
    std::vector<TextLine> create_lines(
        const std::vector<CharsAndWidth>& lines_chars) const;
    bool line_should_be_ended(int line_width, int i, std::string text) const;
    std::vector<CharsAndWidth> slice_text_into_lines(std::string text) const;
    Rectangle create_line_background(Vector2 position, int width) const;
    int compute_aligned_position(
        Align align, int container_size, int content_size) const;
    int compute_lines_position_y(int lines_quantity) const;
    int compute_line_position_x(int line_width) const;
    TextLine create_line(
        const std::vector<Char>& chars, int width, int y) const;

    int compute_lines_height(int lines_quantity) const
    {
        return lines_quantity * Char::height
            + (lines_quantity - 1) * Char::separator;
    }
};

}

#endif