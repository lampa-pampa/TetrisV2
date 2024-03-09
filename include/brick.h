#ifndef INCLUDE_BRICK_H
#define INCLUDE_BRICK_H

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

#include <boost/range/irange.hpp>

#include "cube.h"
#include "vector_2.h"

namespace Tetris
{
inline std::ostream& operator<<(
    std::ostream& os, const std::vector<Cube>& cubes);

struct Brick final
{
    static constexpr int rotation_quantity{4};

    std::vector<Cube> cubes;
    Vector2 rotation_offset;

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

    static Brick get_colored(const Brick& brick, int color_code)
    {
        Brick colored_brick{brick};
        for (auto& cube : colored_brick.cubes)
            cube.color_code = color_code;
        return colored_brick;
    }

    static Brick get_translated(const Brick& brick, Vector2 position)
    {
        Brick translated_brick{brick};
        for (auto& cube : translated_brick.cubes)
            cube.position += position;
        return translated_brick;
    }

    static Vector2 get_rotated_position(
        Vector2 position, Vector2 rotation_offset, int quarters_rotation)
    {
        for (const auto& i : boost::irange(quarters_rotation))
        {
            std::swap(position.x, position.y);
            position.x *= -1;
            position += rotation_offset;
        }
        return position;
    }

    static Brick get_rotated(const Brick& brick, int quarters_rotation)
    {
        Brick rotated_brick{brick};
        for (auto& cube : rotated_brick.cubes)
        {
            cube.position = get_rotated_position(
                cube.position, brick.rotation_offset, quarters_rotation);
        }
        return rotated_brick;
    }

    static Brick get_transformed(
        const Brick& brick, int quarters_rotation, Vector2 position)
    {
        return get_translated(get_rotated(brick, quarters_rotation), position);
    }
    
    Brick(std::vector<Cube> cubes, Vector2 rotation_offset)
    :
        cubes{cubes},
        rotation_offset{rotation_offset}
    {}
        
    Brick(std::vector<Cube> cubes)
    :
        Brick{cubes, {0, 0}}
    {}

    Brick() = default;

    bool operator==(const Brick& other) const
    {
        return this->cubes == other.cubes
            and this->rotation_offset == other.rotation_offset;
    }

    bool empty() const
    {
        return this->cubes.empty();
    }

    int get_min_x() const
    {
        if (this->cubes.empty())
            return 0;
        return std::min_element(
            this->cubes.begin(),
            this->cubes.end(),
            [](const Cube& a, const Cube& b){
                return a.position.x < b.position.x;}
        )->position.x;
    }

    int get_max_x() const
    {
        if (this->cubes.empty())
            return 0;
        return std::max_element(
            this->cubes.begin(),
            this->cubes.end(),
            [](const Cube& a, const Cube& b){
                return a.position.x < b.position.x;}
        )->position.x;
    }

    int get_min_y() const
    {
        if (this->cubes.empty())
            return 0;
        return std::min_element(
            this->cubes.begin(),
            this->cubes.end(),
            [](const Cube& a, const Cube& b){
                return a.position.y < b.position.y;}
        )->position.y;
    }

    int get_max_y() const
    {
        if (this->cubes.empty())
            return 0;
        return std::max_element(
            this->cubes.begin(),
            this->cubes.end(),
            [](const Cube& a, const Cube& b){
                return a.position.y < b.position.y;}
        )->position.y;
    }

    int get_width() const
    {
        if(this->empty())
            return 0;
        return std::abs(this->get_max_x() - this->get_min_x()) + 1;
    }

    int get_height() const
    {
        if(this->empty())
            return 0;
        return std::abs(this->get_max_y() - this->get_min_y()) + 1;
    }
};

inline std::ostream& operator<<(
    std::ostream& os, const std::vector<Cube>& cubes)
{
    for (const auto& cube : cubes)
    {
        os << cube;
        if (&cube != &cubes.back())
            os << ", ";
    }
    return os;
}

}

#endif