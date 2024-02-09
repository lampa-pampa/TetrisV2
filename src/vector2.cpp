#include "vector2.h"


Vector2 Vector2::operator+(Vector2 other)
{
    return {this->x + other.x, this->y + other.y};
}

Vector2 Vector2::operator-(Vector2 other)
{
    return {this->x - other.x, this->y - other.y};
}