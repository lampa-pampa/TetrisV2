#include "board_impl.h"
#include "pixel.h"
#include <vector>

BoardImpl::BoardImpl(std::shared_ptr<BoardUI> &&ui, int width, int height)
:
    ui(std::move(ui)),
    width(width),
    height(height)
{
    this->pixels.resize(height, std::vector<Pixel>(width));
}

int BoardImpl::get_width() const
{
    return this->width;
}