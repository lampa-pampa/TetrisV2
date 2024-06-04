#ifndef INCLUDE_UI_TEXT_AREA_H
#define INCLUDE_UI_TEXT_AREA_H

#include <algorithm>
#include <cassert>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "ui/bitmap/bitmap.h"
#include "ui/rectangle/rectangle.h"
#include "ui/text_area/align.h"
#include "ui/text_area/font/font.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class TextArea final
{
public:
    TextArea(const Rectangle& container,
        const Font& font,
        Align align = Align::end,
        int wrap_after = 3,
        Vector2 separator = {1},
        Vector2 padding = {1})
      : font_{font},
        container_{container},
        align_{align},
        wrap_after_{wrap_after},
        padding_{padding},
        separator_{separator}
    {}

    std::vector<Bitmap> create_lines(std::string text) const;

private:
    using AlignToFuncion = std::map<Align, std::function<int(int, int)>>;

    const inline static AlignToFuncion aligners{
        {
            Align::start,
            [](int container_size, int content_size) { return 0; },
        },
        {
            Align::center,
            [](int container_size, int content_size)
            { return container_size / 2 - content_size / 2; },
        },
        {
            Align::end,
            [](int container_size, int content_size)
            { return container_size - content_size; },
        },
    };

    const Font& font_;
    const Rectangle container_;
    const Align align_;
    const int wrap_after_;
    const Vector2 separator_;
    const Vector2 padding_;

    Bitmap create_line(const std::string& text) const;
    std::vector<std::string> split(std::string text) const;
    std::string wrap(const std::string& text) const;
    std::string put_new_lines(const std::string& text) const;
    void set_lines_positions(std::vector<Bitmap>& lines) const;

    int compute_all_lines_height(int number_of_lines) const
    {
        return number_of_lines * font_.get_height()
            + std::max(number_of_lines - 1, 0) * separator_.y + 2 * padding_.y;
    }

    int compute_all_lines_start_y(int number_of_lines) const
    {
        return container_.position.y
            + aligners.at(align_)(
                container_.size.y, compute_all_lines_height(number_of_lines));
    }

    int compute_line_x(int line_width) const
    {
        return container_.position.x
            + aligners.at(align_)(container_.size.x, line_width);
    }
};

} // namespace Tetris::Ui

#endif
