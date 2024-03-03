#ifndef INCLUDE_BRICK_H
#define INCLUDE_BRICK_H

#include <algorithm>
#include <vector>

#include "cube.h"
#include "vector_2.h"

namespace Tetris
{

struct Brick final
{
    static constexpr int rotation_quantity{4};

    std::vector<Cube> cubes;
    Vector2 rotation_offset;

    friend std::ostream& operator<<(std::ostream& os, const Brick& brick);

    static Brick get_colored(const Brick& brick, int color_code);
    static Brick get_translated(const Brick& brick, Vector2 position);
    static Brick get_rotated(const Brick& brick, int quarters_rotation);
    static Brick get_ghostified(const Brick& brick);
    static Brick get_transformed(
        const Brick& brick,
        int quarters_rotation,
        Vector2 position
    ){
        const Brick rotated_brick{Brick::get_rotated(
            brick,
            quarters_rotation
        )};
        return Brick::get_translated(rotated_brick, position);
    }

    bool operator==(const Brick& other) const
    {
        return this->cubes == other.cubes
            and this->rotation_offset == other.rotation_offset;
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

    bool empty() const
    {
        return this->cubes.empty();
    }

    int get_min_x() const
    {
        return std::min_element(
            this->cubes.begin(),
            this->cubes.end(),
            [](const Cube& a, const Cube& b){
                return a.position.x < b.position.x;
            }
        )->position.x;
    }

    int get_max_x() const
    {
        return std::max_element(
            this->cubes.begin(),
            this->cubes.end(),
            [](const Cube& a, const Cube& b){
                return a.position.x < b.position.x;
            }
        )->position.x;
    }

    int get_min_y() const
    {
        return std::min_element(
            this->cubes.begin(),
            this->cubes.end(),
            [](const Cube& a, const Cube& b){
                return a.position.y < b.position.y;
            }
        )->position.y;
    }

    int get_max_y() const
    {
        return std::max_element(
            this->cubes.begin(),
            this->cubes.end(),
            [](const Cube& a, const Cube& b){
                return a.position.y < b.position.y;
            }
        )->position.y;
    }
};

}

#endif