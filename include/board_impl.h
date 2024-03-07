#ifndef INCLUDE_BOARD_IMPL_H
#define INCLUDE_BOARD_IMPL_H

#include "board.h"

#include <cassert>
#include <vector>

#include <boost/range/irange.hpp>

#include "cube.h"
#include "vector_2.h"

namespace Tetris
{

class BoardImpl final: public Board
{
public:
    BoardImpl(int width, int height, int offset)
    :
        width{width},
        height{height + offset},
        offset{offset}
    {
        this->cubes = this->create_cubes();
    }

    BoardImpl(int width, int height)
    :
        BoardImpl(width, height, 0)
    {}

    void put_cubes(const std::vector<Cube>& cubes) override
    {
        for (const auto& cube : cubes)
        {
            assert(this->position_is_in_range(cube.position));
            this->cubes[cube.position.y][cube.position.x] = cube;
        }
    }

    std::vector<int> remove_lines_and_compress(int from_y, int to_y) override
    {
        assert(this->position_is_in_range({0, from_y})
            and this->position_is_in_range({0, to_y}));
        const std::vector rows{this->find_rows_with_line(from_y, to_y)};
        for (const auto& y : rows)
            this->compress(y);
        return rows;
    }
    
    bool brick_is_valid(const Brick& brick) const override 
    {
        for (const auto& cube : brick.cubes)
        {
            if (not this->position_is_valid(cube.position))
                return false;
        }
        return true;
    }

    int get_width() const override
    {
        return this->width;
    }

    int get_offset() const override
    {
        return this->offset;
    }

    CubeMatrix get_visible_cubes() const override
    {
        return {this->cubes.begin() + this->offset, this->cubes.end()};
    }

    std::vector<Cube> get_visible_brick_cubes(
        const std::vector<Cube>& cubes) const override
    {
        std::vector<Cube> visible_cubes{};
        for (const auto& cube : cubes)
        {
            if (cube.position.y >= this->offset)
                visible_cubes.push_back(cube);
        }
        return visible_cubes;
    }

    CubeMatrix get_cubes() const
    {
        return this->cubes;
    }

private:
    const int width;
    const int height;
    const int offset;
    CubeMatrix cubes;
    
    CubeMatrix create_cubes() const
    {
        CubeMatrix cubes;
        for (const auto& y : boost::irange(this->height))
        {
            std::vector<Cube> row{};
            for (const auto& x : boost::irange(this->width))
                row.emplace_back(Cube{x, y});
            cubes.emplace_back(std::move(row));
        }
        return cubes;
    }
    
    std::vector<int> find_rows_with_line(int from_y, int to_y) const
    {
        std::vector<int> line_positions;
        for (const auto& y : boost::irange(from_y, to_y + 1))
        {
            if (this->is_row_with_line(y))
                line_positions.push_back(y);
        }
        return line_positions;
    }

    bool is_row_with_line(int y) const
    {
        for (const auto& cube : this->cubes[y])
        {
            if (cube.empty())
                return false;
        }
        return true;
    }

    Brick try_to_create_line(int y) const
    {
        Brick line{};
        for (const auto& cube : this->cubes[y])
        {
            if (cube.empty())
                return {};
            line.cubes.push_back(cube);
        }
        return line;
    }

    void copy_cube_above(Vector2 position)
    {
        const Cube& above{this->cubes[position.y - 1][position.x]};
        this->cubes[position.y][position.x].color_code = above.color_code;
    }

    void compress(int start_y)
    {
        for (const auto& y : boost::irange(start_y, 0, -1))
        {
            for (const auto& cube : this->cubes[y])
                this->copy_cube_above(cube.position);
        }
        this->clear_top_row();
    }

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

    void clear_top_row()
    {
        for (auto& cube : this->cubes[0])
            cube.clear();
    }

};

}

#endif