#include "ui/progress_bar.h"

#include <vector>

#include <boost/range/irange.hpp>

#include "ui/rectangle.h"
#include "vector_2.h"

namespace Tetris::Ui
{

ProgressBar::ProgressBar(
    Vector2 position,
    int height,
    int separator,
    const Rectangle& segment,
    IvColor empty_segment_iv_color)
:
    position{position},
    height{height},
    separator{separator},
    segment{segment},
    empty_segment_iv_color{empty_segment_iv_color}
{}

std::vector<Rectangle> ProgressBar::create_segments(int value) const
{
    std::vector<Rectangle> segments;
    Vector2 segment_position = this->position; 
    for(const auto& i : boost::irange(this->height))
    {
        Rectangle cur_segment = this->segment;
        if(value < this->height - i)
            cur_segment.iv_color = empty_segment_iv_color;
        cur_segment.position = segment_position;
        segments.emplace_back(std::move(cur_segment));
        segment_position.y += this->segment.height + this->separator;
    }
    return segments;
}

}