#ifndef COLOR_H
#define COLOR_H

#include <map>
#include <string>

enum class Color
{
    black,
    red,
    green,
    blue,
    yellow,
    purple,
    orange,
    pink,
};

const std::map<Color, std::string> ColorToName{
    {Color::black, "black"},
    {Color::red, "red"},
    {Color::green, "green"},
    {Color::blue, "blue"},
    {Color::yellow, "yellow"},
    {Color::purple, "purple"},
    {Color::orange, "orange"},
    {Color::pink, "pink"},
};

#endif