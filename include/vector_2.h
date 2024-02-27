#ifndef VECTOR_2_H
#define VECTOR_2_H

#include <ostream>

struct Vector2 final
{
    int x;
    int y;
    
    Vector2& operator+=(Vector2 other)
    {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    bool operator==(const Vector2 &other) const
    {
        return this->x == other.x
            and this->y == other.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector2)
    {
        return os << "{" << vector2.x << ", " << vector2.y << "}";
    }
};

#endif