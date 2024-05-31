#ifndef INCLUDE_UI_PROGRESS_BAR_H
#define INCLUDE_UI_PROGRESS_BAR_H

#include <tuple>
#include <vector>

#include "ui/rectangle/rectangle.h"
#include "vector_2/vector_2.h"

namespace Tetris::Ui
{

class ProgressBar final
{
public:
    using Segments = std::tuple<std::vector<Rectangle>, std::vector<Rectangle>>;

    constexpr ProgressBar(
        Vector2 position, Vector2 segment_size, int height, int separator)
      : position_{position},
        segment_size_{segment_size},
        height_{height},
        separator_{separator}
    {}

    Segments create_segments(int value) const;

private:
    Vector2 position_;
    Vector2 segment_size_;
    int height_;
    int separator_;
};

} // namespace Tetris::Ui

#endif
