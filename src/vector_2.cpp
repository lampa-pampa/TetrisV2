#include "vector_2.h"

Vector2 Vector2::operator+(Vector2 other) const
{
    return {this->x + other.x, this->y + other.y};
}

Vector2 Vector2::operator-(Vector2 other) const
{
    return {this->x - other.x, this->y - other.y};
}