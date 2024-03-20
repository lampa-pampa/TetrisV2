#include "ui/progress_bar.h"

#include <vector>

#include <boost/range/irange.hpp>

#include "ui/rectangle.h"
#include "vector_2.h"

namespace Tetris::Ui
{

ProgressBar::Segments ProgressBar::create_segments(int value) const
{
    std::vector<Rectangle> on_segments;
    std::vector<Rectangle> off_segments;
    Vector2 segment_position = this->position; 
    for (const auto& i : boost::irange(this->height))
    {
        const Rectangle segment{
            segment_position, this->segment_width, this->segment_height
        };      
        if (value >= this->height - i)
            on_segments.emplace_back(std::move(segment));
        else
            off_segments.emplace_back(std::move(segment));
        
        segment_position.y += this->segment_height + this->separator;
    }
    return {std::move(on_segments), std::move(off_segments)};
}

}