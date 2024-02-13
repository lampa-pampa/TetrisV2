#include "board_impl.h"
#include "pixel.h"
#include <vector>

using std::vector;

BoardImpl::BoardImpl(int width, int height)
:
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