#ifndef INCLUDE_UI_ALIGN_H
#define INCLUDE_UI_ALIGN_H

#include <map>
#include <ostream>
#include <string>

namespace Tetris
{

enum class Align
{
    start,
    center,
    end,
};

namespace
{

const std::map<Align, std::string> align_to_name
{
    {Align::start, "start"},
    {Align::center, "center"},
    {Align::end, "end"},
};

}

inline std::ostream& operator<<(std::ostream& os, Align align)
{
    return os << "Align::" << align_to_name.at(align);
}

}

#endif