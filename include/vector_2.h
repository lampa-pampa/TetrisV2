#ifndef INCLUDE_VECTOR_2_H
#define INCLUDE_VECTOR_2_H

#include <cstdlib>
#include <ostream>

namespace Tetris
{

struct Vector2 final
{
    int x;
    int y;

    constexpr Vector2(int x, int y)
    :
        x{x},
        y{y}
    {}

    constexpr Vector2(int a)
    :
        Vector2{a, a}
    {}

    Vector2() = default;

    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector2)
    {
        return os << "{" << vector2.x << ", " << vector2.y << "}";
    }

    Vector2 abs() const
    {
        return {::abs(this->x), ::abs(this->y)};
    }

    Vector2 center() const
    {
        return {this->x / 2, this->y / 2};
    }

    Vector2 scale(const Vector2& other) const
    {
        return {this->x * other.x, this->y * other.y};
    }

    bool operator>(const Vector2& other) const
    {
        return this->x > other.x and this->y > other.y; 
    }

    bool operator<(const Vector2& other) const
    {
        return this->x < other.x and this->y < other.y; 
    }

    bool operator==(const Vector2& other) const
    {
        return this->x == other.x and this->y == other.y;
    }

    bool operator>=(const Vector2& other) const
    {
        return this->x >= other.x and this->y >= other.y; 
    }

    bool operator<=(const Vector2& other) const
    {
        return this->x <= other.x and this->y <= other.y;
    }

    Vector2 operator+(const Vector2& other) const
    {
        return {this->x + other.x, this->y + other.y};
    }

    Vector2 operator-(const Vector2& other) const
    {
        return {this->x - other.x, this->y - other.y};
    }

    Vector2& operator+=(const Vector2& other)
    {
        return *this = *this + other;
    }

    Vector2& operator-=(const Vector2& other)
    {
        return *this = *this - other;
    }
};

}

#endif