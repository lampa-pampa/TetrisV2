#include "board_impl.h"
#include "brick.h"
#include "pixel.h"
#include "vector_2.h"
#include <vector>

using std::vector;

BoardImpl::BoardImpl(int width, int height)
:
    width(width),
    height(height)
{
    for (int y{0}; y < height; ++y)
    {
        vector<Pixel> row;
        for (int x{0}; x < width; ++x)
            row.emplace_back(Pixel{x, y});
        this->pixels.emplace_back(std::move(row));
    }
}

bool BoardImpl::is_space_for_brick(const Brick& brick) const 
{
    for (const Pixel& pixel : brick.pixels)
    {
        if (not this->position_is_in_range(pixel.coords)
            or not this->pixels[pixel.coords.y][pixel.coords.x].empty())
            return false;
    }
    return true;
}

void BoardImpl::add_brick(const Brick& brick)
{
    for (const Pixel& pixel : brick.pixels)
        this->pixels[pixel.coords.y][pixel.coords.x] = pixel;
}

void BoardImpl::remove_brick(const Brick& brick)
{
    for (const Pixel& pixel : brick.pixels)
        this->pixels[pixel.coords.y][pixel.coords.x].clear();
}

vector<Brick> BoardImpl::find_lines_in_range(int from_y, int to_y) const
{
    vector<Brick> lines;
    for (int y{from_y}; y <= to_y; ++y)
    {
        Brick line{{}};
        bool is_full_line{true};
        for (int x{0}; x < this->width; ++x)
        {
            const Pixel& pixel = this->pixels[y][x];
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
    for (int y{start_y}; y > 0; --y)
    {
        for (int x{0}; x < this->width; ++x)
        {
            this->pixels[y][x] = this->pixels[y - 1][x];
            this->pixels[y][x].coords = {x, y};
        }
    }
    for (int x{0}; x < this->width; ++x)
        this->pixels[0][x].clear();
}

int BoardImpl::remove_lines_in_range_and_compress(int from_y, int to_y)
{
    vector<Brick> lines{this->find_lines_in_range(from_y, to_y)};
    for (const auto& line : lines)
    {
        this->remove_brick(line);
        this->compress(line.pixels[0].coords.y);
    }
    return lines.size();
}