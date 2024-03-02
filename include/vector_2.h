#ifndef INCLUDE_VECTOR_2_H
#define INCLUDE_VECTOR_2_H

#include <ostream>

namespace Tetris
{

struct Vector2 final
{
    int x;
    int y;

    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector2)
    {
        return os << "{" << vector2.x << ", " << vector2.y << "}";
    }
    
    Vector2& operator+=(const Vector2& other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Vector2 operator+(const Vector2& other) const
    {
        return {this->x + other.x, this->y + other.y};
    }

    bool operator==(const Vector2& other) const
    {
        return this->x == other.x
            and this->y == other.y;
    }
};

}

#endif