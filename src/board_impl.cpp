#include "board_impl.h"

#include <cassert>
#include <vector>

#include <boost/range/irange.hpp>

#include "brick.h"
#include "pixel.h"
#include "vector_2.h"

namespace Tetris
{

using std::vector;
using boost::irange;

vector<Brick> BoardImpl::find_lines_in_range(int from_y, int to_y) const
{
    vector<Brick> lines;
    for (const auto& y : irange(from_y, to_y + 1))
    {
        Brick line{};
        bool is_full_line{true};
        for (const auto& x : irange(this->width))
        {
            const Pixel& pixel{this->pixels[y][x]};
            if (pixel.empty())
            {
                is_full_line = false;
                break;
            }
            line.pixels.push_back(pixel);
        }
        if (is_full_line)
            lines.emplace_back(std::move(line));
    }
    return lines;
}

void BoardImpl::compress(int start_y)
{
    for (const auto& y : irange(start_y, 0, -1))
    {
        for (const auto& x : irange(this->width))
        {
            this->pixels[y][x] = this->pixels[y - 1][x];
            this->pixels[y][x].coords = {x, y};
        }
    }
    for (const auto& x : irange(this->width))
        this->pixels[0][x].clear();
}

BoardImpl::BoardImpl(int width, int height)
:
    width(width),
    height(height)
{
    for (const auto& y : irange(height))
    {
        vector<Pixel> row;
        for (const auto& x : irange(width))
            row.emplace_back(Pixel{x, y});
        this->pixels.emplace_back(std::move(row));
    }
}

bool BoardImpl::is_space_for_brick(const Brick& brick) const 
{
    for (const auto& pixel : brick.pixels)
    {
        if (not this->position_is_in_range(pixel.coords)
            or not this->pixels[pixel.coords.y][pixel.coords.x].empty())
            return false;
    }
    return true;
}

void BoardImpl::put_pixels(const vector<Pixel>& pixels)
{
    for (const auto& pixel : pixels)
    {
        assert(this->position_is_in_range(pixel.coords));
        this->pixels[pixel.coords.y][pixel.coords.x] = pixel;
    }
}

void BoardImpl::clear_pixels(const vector<Pixel>& pixels)
{
    for (const auto& pixel : pixels)
    {
        assert(this->position_is_in_range(pixel.coords));
        this->pixels[pixel.coords.y][pixel.coords.x].clear();
    }
}

int BoardImpl::remove_lines_in_range_and_compress(int from_y, int to_y)
{
    const vector lines{this->find_lines_in_range(from_y, to_y)};
    for (const auto& line : lines)
    {
        this->clear_pixels(line.pixels);
        this->compress(line.pixels[0].coords.y);
    }
    return lines.size();
}

}