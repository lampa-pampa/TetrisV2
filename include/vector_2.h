#ifndef VECTOR_2_H
#define VECTOR_2_H

struct Vector2
{
    int x;
    int y;
    Vector2 operator+(Vector2 other) const;
    Vector2 operator-(Vector2 other) const;
    bool operator==(const Vector2 &other) const;
};

#endif