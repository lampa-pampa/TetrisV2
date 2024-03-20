#ifndef INCLUDE_UI_PROGRESS_BAR_H
#define INCLUDE_UI_PROGRESS_BAR_H

#include <tuple>
#include <vector>

#include "rectangle.h"
#include "vector_2.h"

namespace Tetris::Ui
{

class ProgressBar final
{
public:
    using Segments = std::tuple<
        std::vector<Rectangle>, std::vector<Rectangle>>;

    constexpr ProgressBar(
    Vector2 position,
    int segment_width,
    int segment_height,
    int height,
    int separator)
:
    position{position},
    segment_width{segment_width},
    segment_height{segment_height},
    height{height},
    separator{separator}
{}

    Segments create_segments(int value) const;

private:
    Vector2 position;
    int height;
    int separator;
    int segment_width;
    int segment_height;
};

}

#endif