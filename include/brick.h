#ifndef INCLUDE_BRICK_H
#define INCLUDE_BRICK_H

#include <cstdint>
#include <ostream>
#include <vector>

#include "cube.h"
#include "vector_2.h"

namespace Tetris
{

std::ostream& operator<<(std::ostream& os, const std::vector<Cube>& cubes);

struct Brick final
{
    static constexpr int rotation_quantity{4};

    std::vector<Cube> cubes;
    Vector2 rotation_offset;

    static Brick get_translated(const Brick& brick, Vector2 position);
    static Vector2 get_rotated_position(
        Vector2 position, Vector2 rotation_offset, int quarters_rotation);
    static Brick get_rotated(const Brick& brick, int quarters_rotation);
    static Brick get_colored(const Brick& brick, uint_fast8_t color_id);

    friend inline std::ostream& operator<<(
        std::ostream& os, const Brick& brick)
    { 
        return os << "{{ " << brick.cubes << " }, "
            << brick.rotation_offset << "}";
    }

    static int compute_next_rotation(int rotation, int d_q)
    {
        return (rotation + d_q + rotation_quantity) % rotation_quantity;
    }

    static Brick get_transformed(
        const Brick& brick, int quarters_rotation, Vector2 position)
    {
        return get_translated(get_rotated(brick, quarters_rotation), position);
    }
    
    Brick(std::vector<Cube> cubes = {}, Vector2 rotation_offset = {0, 0})
    :
        cubes{cubes},
        rotation_offset{rotation_offset}
    {}
    
    int get_min_x() const;
    int get_max_x() const;
    int get_min_y() const;
    int get_max_y() const;
    Vector2 get_size() const;

    bool operator==(const Brick& other) const
    {
        return cubes == other.cubes
            and rotation_offset == other.rotation_offset;
    }

    bool empty() const
    {
        return cubes.empty();
    }
};

}

#endif