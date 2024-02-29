#ifndef INCLUDE_COLOR_H
#define INCLUDE_COLOR_H

#include <map>
#include <ostream>
#include <string>

namespace Tetris
{

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
    white,
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
    {Color::white, "pink"},
};

inline std::ostream& operator<<(std::ostream& os, Color color)
{
    return os << "Color::" << color_to_name.at(color);
}

}

#endif