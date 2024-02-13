#include "board_impl.h"
#include "pixel.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

BoardImpl::BoardImpl(unique_ptr<BoardUI> &&ui, int width, int height)
:
    ui(std::move(ui)),
    width(width),
    height(height)
{
    for(int y{0}; y < height; ++y)
    {
        vector<Pixel> row;
        for(int x{0}; x < width; ++x)
            row.emplace_back(Pixel{{x, y}});
        this->pixels.emplace_back(std::move(row));
    }
}

vector<vector<Pixel>> BoardImpl::get_pixels() const
{
    return this->pixels;
}

int BoardImpl::get_width() const
{
    return this->width;
}