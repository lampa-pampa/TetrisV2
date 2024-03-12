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
    BoardImpl(int width, int height, int offset);
    BoardImpl(int width, int height): BoardImpl(width, height, 0){}
    void put_cubes(const std::vector<Cube>& cubes) override;
    std::vector<int> remove_lines_and_compress(int from_y, int to_y) override;
    bool brick_is_valid(const Brick& brick) const override;
    std::vector<Cube> get_visible_brick_cubes(
        const std::vector<Cube>& cubes) const override;

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

    CubeMatrix get_cubes() const
    {
        return this->cubes;
    }

private:
    const int width;
    const int height;
    const int offset;
    CubeMatrix cubes;
    
    CubeMatrix create_cubes() const;
    std::vector<int> find_rows_with_line(int from_y, int to_y) const;
    bool is_row_with_line(int y) const;
    Brick try_to_create_line(int y) const;
    void compress(int start_y);

    void copy_cube_above(Vector2 position)
    {
        const Cube& above{this->cubes[position.y - 1][position.x]};
        this->cubes[position.y][position.x].color_code = above.color_code;
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