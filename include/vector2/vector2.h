#ifndef INCLUDE_VECTOR2_H
#define INCLUDE_VECTOR2_H

#include <cstdlib>
#include <ostream>
#include <vector>

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

    constexpr Vector2(int x, int y): x{x}, y{y} {}
    constexpr Vector2(int a): Vector2{a, a} {}
    Vector2() = default;

    Vector2 abs() const
    {
        return {::abs(x), ::abs(y)};
    }

    Vector2 center() const
    {
        return {x / 2, y / 2};
    }

    Vector2 scale(const Vector2& other) const
    {
        return {x * other.x, y * other.y};
    }

    bool operator>(const Vector2& other) const
    {
        return x > other.x and y > other.y;
    }

    bool operator<(const Vector2& other) const
    {
        return x < other.x and y < other.y;
    }

    bool operator==(const Vector2& other) const
    {
        return x == other.x and y == other.y;
    }

    bool operator>=(const Vector2& other) const
    {
        return x >= other.x and y >= other.y;
    }

    bool operator<=(const Vector2& other) const
    {
        return x <= other.x and y <= other.y;
    }

    Vector2 operator+(const Vector2& other) const
    {
        return {x + other.x, y + other.y};
    }

    Vector2 operator-(const Vector2& other) const
    {
        return {x - other.x, y - other.y};
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

inline std::ostream& operator<<(
    std::ostream& os, const std::vector<Vector2>& vectors)
{
    os << "{";
    for (const auto& vector2 : vectors)
    {
        os << vector2;
        if (&vector2 != &vectors.back())
            os << ", ";
    }
    return os << "}";
}

} // namespace Tetris

#endif
