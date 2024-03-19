#ifndef INCLUDE_UI_PROGRESS_BAR
#define INCLUDE_UI_PROGRESS_BAR

#include <vector>

#include "ui/iv_color.h"
#include "ui/rectangle.h"
#include "vector_2.h"

namespace Tetris::Ui
{

class ProgressBar final
{
public:
    ProgressBar(
        Vector2 position,
        int range,
        int separator,
        const Rectangle& segment,
        IvColor empty_segment_iv_color);

    std::vector<Rectangle> create_segments(int value) const;

private:
    Vector2 position;
    int height;
    int separator;
    Rectangle segment;
    IvColor empty_segment_iv_color;
};

}

#endif