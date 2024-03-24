#include "ui/progress_bar.h"

#include <vector>

#include <boost/range/irange.hpp>

#include "ui/rectangle.h"
#include "vector_2.h"

using boost::irange;
using std::vector;

namespace Tetris::Ui
{

ProgressBar::Segments ProgressBar::create_segments(int value) const
{
    vector<Rectangle> on_segments;
    vector<Rectangle> off_segments;
    Vector2 segment_position = position_; 
    for (const auto& i : irange(height_))
    {
        const Rectangle segment{segment_position, segment_size_};      
        if (height_ - i <= value)
            on_segments.emplace_back(std::move(segment));
        else
            off_segments.emplace_back(std::move(segment));
        
        segment_position.y += segment_size_.y + separator_;
    }
    return {std::move(on_segments), std::move(off_segments)};
}

}