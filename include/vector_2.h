#ifndef VECTOR_2_H
#define VECTOR_2_H

#include <ostream>

struct Vector2
{
    int x;
    int y;
    
    Vector2& operator+=(Vector2 other);
    bool operator==(const Vector2 &other) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector2);
};

#endif