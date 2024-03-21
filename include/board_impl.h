#ifndef INCLUDE_BOARD_IMPL_H
#define INCLUDE_BOARD_IMPL_H

#include "board.h"

#include <vector>

#include "brick.h"
#include "cube.h"
#include "vector_2.h"

namespace Tetris
{

class BoardImpl final: public Board
{
public:
    BoardImpl(Vector2 size, int offset = 0);
    
    void put_cubes(const std::vector<Cube>& cubes) override;
    std::vector<int> remove_lines_and_compress(int from_y, int to_y) override;
    bool brick_is_valid(const Brick& brick) const override;
    std::vector<Cube> get_visible_brick_cubes(
        const std::vector<Cube>& cubes) const override;

    int get_offset() const override
    {
        return this->offset;
    }

    CubeMatrix get_visible_cubes() const override
    {
        return {this->cubes.begin() + this->offset, this->cubes.end()};
    }

    CubeMatrix get_cubes() const
    {
        return this->cubes;
    }

private:
    const Vector2 size;
    const int offset;
    CubeMatrix cubes;
    
    CubeMatrix create_cubes() const;
    std::vector<int> find_rows_with_line(int from_y, int to_y) const;
    bool is_row_with_line(int y) const;
    Brick try_to_create_line(int y) const;
    void compress(int start_y);

    std::vector<Cube>& get_row(int y)
    {
        return this->cubes[y + this->offset];
    }

    const std::vector<Cube>& get_row(int y) const
    {
        return this->cubes[y + this->offset];
    }
    
    Cube& get_cube(Vector2 position)
    {
        return this->get_row(position.y)[position.x];
    }

    const Cube& get_cube(Vector2 position) const
    {
        return this->get_row(position.y)[position.x];
    }

    void copy_cube_above(Vector2 position)
    {
        const Cube& above{this->get_cube(position - Vector2{0, 1})};
        this->get_cube(position).color_id = above.color_id;
    }

    bool position_is_valid(Vector2 position) const
    {
        return this->position_is_in_range(position)
            and this->get_cube(position).empty();
    }

    bool position_is_in_range(Vector2 position) const
    {
        return position.x >= 0 and position.x < this->size.x
            and position.y >= -this->offset and position.y < this->size.y;
    }

    void clear_top_row()
    {
        for (auto& cube : this->get_row(-this->offset))
            cube.clear();
    }
};

}

#endif