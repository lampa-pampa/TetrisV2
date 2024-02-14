#include "board_impl.h"
#include "pixel.h"
#include "vector_2.h"
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

const vector<vector<Pixel>>& BoardImpl::get_pixels() const
{
    return this->pixels;
}

int BoardImpl::get_width() const
{
    return this->width;
}

bool BoardImpl::position_is_in_range(Vector2 position) const
{
    return position.x >= 0 and position.x < this->width
        and position.y >= 0 and position.y < this->height;
}

bool BoardImpl::is_space_for_brick(const Brick &brick) const 
{
    for(const Pixel &pixel : brick.pixels)
    {
        if(not this->position_is_in_range(pixel.coords)
            or not this->pixels[pixel.coords.y][pixel.coords.x].empty())
            return false;
    }
    return true;
}

void BoardImpl::add_brick(const Brick &brick)
{
    for(const Pixel &pixel : brick.pixels)
        this->pixels[pixel.coords.y][pixel.coords.x] = pixel;
}

void BoardImpl::remove_brick(const Brick &brick)
{
    for(const Pixel &pixel : brick.pixels)
        this->pixels[pixel.coords.y][pixel.coords.x].clear();
}