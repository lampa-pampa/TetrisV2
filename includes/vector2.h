#ifndef COORDS_H
#define COORDS_H

struct Vector2
{
    int x;
    int y;
    Vector2 operator+(Vector2 other);
    Vector2 operator-(Vector2 other);
};

#endif