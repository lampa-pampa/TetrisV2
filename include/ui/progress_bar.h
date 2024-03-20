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
        Vector2 segment_size,
        int height,
        int separator)
    :
        position{position},
        segment_size{segment_size},
        height{height},
        separator{separator}
    {}

    Segments create_segments(int value) const;

private:
    Vector2 position;
    Vector2 segment_size;
    int height;
    int separator;
};

}

#endif