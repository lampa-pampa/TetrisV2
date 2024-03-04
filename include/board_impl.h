#ifndef INCLUDE_BOARD_IMPL_H
#define INCLUDE_BOARD_IMPL_H

#include <cassert>
#include <vector>

#include "board.h"
#include "brick.h"
#include "cube.h"
#include "vector_2.h"

namespace Tetris
{

class BoardImpl final: public Board
{
    using CubeMatrix = std::vector<std::vector<Cube>>;

    const int width;
    const int height;
    CubeMatrix cubes;
    
    std::vector<Brick> find_lines_in_range(int from_y, int to_y) const;
    void compress(int start_y);
    
    bool position_is_valid(Vector2 position) const
    {
        return this->position_is_in_range(position)
            and this->cubes[position.y][position.x].empty();
    }

    bool position_is_in_range(Vector2 position) const
    {
        return position.x >= 0 and position.x < this->width
            and position.y >= 0 and position.y < this->height;
    }

public:
    BoardImpl(int width, int height);

    int remove_lines_and_compress(int from_y, int to_y) override;
    
    bool brick_is_valid(const Brick& brick) const override 
    {
        for (const auto& cube : brick.cubes)
        {
            if (not this->position_is_valid(cube.position))
                return false;
        }
        return true;
    }

    void put_cubes(const std::vector<Cube>& cubes) override
    {
        for (const auto& cube : cubes)
        {
            assert(this->position_is_in_range(cube.position));
            this->cubes[cube.position.y][cube.position.x] = cube;
        }
    }

    void clear_cubes(const std::vector<Cube>& cubes) override
    {
        for (const auto& cube : cubes)
        {
            assert(this->position_is_in_range(cube.position));
            this->cubes[cube.position.y][cube.position.x].clear();
        }
    }

    int get_width() const override
    {
        return this->width;
    }

    const CubeMatrix& get_cubes() const override
    {
        return this->cubes;
    }

    CubeMatrix get_cubes(int offset) const override
    {
        return {this->cubes.begin() + offset, this->cubes.end()};
    }
};

}

#endif