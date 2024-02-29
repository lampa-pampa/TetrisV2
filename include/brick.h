#ifndef INCLUDE_BRICK_H
#define INCLUDE_BRICK_H

#include "color.h"
#include "pixel.h"
#include "vector_2.h"
#include <algorithm>
#include <vector>

namespace Tetris
{

struct Brick final
{
    std::vector<Pixel> pixels;
    bool is_center_moved;

    friend std::ostream& operator<<(std::ostream& os, const Brick& brick);
    
    bool operator==(const Brick& other) const
    {
        return this->pixels == other.pixels
            and this->is_center_moved == other.is_center_moved;
    }

    static constexpr unsigned short rotation_quantity{4};
    static Brick get_colored(const Brick& brick, Color color);
    static Brick get_translated(const Brick& brick, Vector2 position);
    static Brick get_rotated(const Brick& brick, int quarters_rotation);
    static Brick get_ghostified(const Brick& brick);
    static Brick get_transformed(
        const Brick& brick,
        int quarters_rotation,
        Vector2 position
    ){
        const Brick rotated_brick{
            Brick::get_rotated(brick, quarters_rotation)
        };
        return Brick::get_translated(rotated_brick, position);
    }
    
    Brick(std::vector<Pixel> pixels, bool is_center_moved)
    :
        pixels{pixels},
        is_center_moved{is_center_moved}
    {}
        
    Brick(std::vector<Pixel> pixels)
    :
        Brick{pixels, false}
    {}

    Brick()
    :
        Brick{{}, false}
    {}

    bool empty() const
    {
        return this->pixels.empty();
    }

    int get_min_x() const
    {
        return std::min_element(
            this->pixels.begin(),
            this->pixels.end(),
            [](const Pixel& a, const Pixel& b){
                return a.coords.x < b.coords.x;
            }
        )->coords.x;
    }

    int get_max_x() const
    {
        return std::max_element(
            this->pixels.begin(),
            this->pixels.end(),
            [](const Pixel& a, const Pixel& b){
                return a.coords.x < b.coords.x;
            }
        )->coords.x;
    }

    int get_min_y() const
    {
        return std::min_element(
            this->pixels.begin(),
            this->pixels.end(),
            [](const Pixel& a, const Pixel& b){
                return a.coords.y < b.coords.y;
            }
        )->coords.y;
    }

    int get_max_y() const
    {
        return std::max_element(
            this->pixels.begin(),
            this->pixels.end(),
            [](const Pixel& a, const Pixel& b){
                return a.coords.y < b.coords.y;
            }
        )->coords.y;
    }
};

}

#endif