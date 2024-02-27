#ifndef COLOR_H
#define COLOR_H

#include <map>
#include <string>

enum class Color
{
    black,
    red,
    green,
    yellow,
    blue,
    purple,
    orange,
    pink,
};

const std::map<Color, std::string> color_to_name
{
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