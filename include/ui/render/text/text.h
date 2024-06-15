#ifndef INCLUDE_UI_RENDER_TEXT_H
#define INCLUDE_UI_RENDER_TEXT_H

#include <functional>
#include <map>
#include <vector>

#include "ui/color/nv_color.h"
#include "ui/render/container/container.h"
#include "ui/render/rectangle.h"
#include "ui/render/sprite.h"
#include "ui/render/text/align.h"
#include "ui/render/text/font/font.h"
#include "vector2/vector2.h"

namespace Tetris::Ui
{

struct TextLine final
{
    Vector2 position;
    int width;
    std::vector<Vector2> text;
};

class RenderText final
{
public:
    using TextLines = std::vector<TextLine>;

    RenderText(const Rectangle& container,
        RenderContainer render_container,
        const Font& font,
        NvColor font_color,
        Align align = Align::end,
        int wrap_after = 3,
        Vector2 separator = {1},
        bool fill_background = true);

    Sprites render(std::string text) const;
    Sprites render(unsigned long long number, int max_length) const;

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

    const Rectangle container_;
    const RenderContainer render_container_;
    const Font& font_;
    const NvColor font_color_;
    const Align align_;
    const int wrap_after_;
    const Vector2 separator_;
    const bool fill_background_;

    TextLines create_lines(const std::string& text) const;
    TextLine create_line(const std::string& text) const;
    std::vector<std::string> split(std::string text) const;
    std::string wrap(const std::string& text) const;
    std::string put_line_breaks(const std::string& text) const;
    void set_lines_positions(TextLines& lines, int start_y) const;
    Rectangle create_text_container(
        const TextLines& lines, int start_y, int all_lines_height) const;
    Sprites transform_to_sprites(
        const TextLines& lines, const Rectangle& text_container) const;

    int compute_all_lines_height(int number_of_lines) const
    {
        return number_of_lines * font_.get_height()
            + std::max(number_of_lines - 1, 0) * separator_.y;
    }

    int compute_all_lines_start_y(int all_lines_height) const
    {
        return container_.position.y
            + aligners.at(align_)(container_.size.y, all_lines_height);
    }

    int compute_line_x(int line_width) const
    {
        return container_.position.x
            + aligners.at(align_)(container_.size.x, line_width);
    }
};

} // namespace Tetris::Ui

#endif
