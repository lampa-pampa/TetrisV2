#include "vector_2.h"
#include <ostream>

using std::ostream;

Vector2& Vector2::operator+=(Vector2 other)
{
    this->x += other.x;
    this->y += other.y;
    return *this;
}

bool Vector2::operator==(const Vector2 &other) const
{
    return this->x == other.x
        and this->y == other.y;
}

ostream& operator<<(ostream& os, const Vector2& vector2)
{
    return os << "{" << vector2.x << ", " << vector2.y << "}";
}