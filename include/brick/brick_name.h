#ifndef INCLUDE_BRICK_NAME_H
#define INCLUDE_BRICK_NAME_H

#include <map>
#include <ostream>
#include <string>

namespace Tetris
{

enum class BrickName
{
    empty,
    custom,
    O,
    I,
    Z,
    S,
    T,
    L,
    J,
};

const std::map<BrickName, std::string> brick_name_to_text{
    {BrickName::empty, "empty"},
    {BrickName::O, "O"},
    {BrickName::I, "I"},
    {BrickName::Z, "Z"},
    {BrickName::S, "S"},
    {BrickName::T, "T"},
    {BrickName::L, "J"},
    {BrickName::J, "L"},
};

inline std::ostream& operator<<(std::ostream& os, BrickName name)
{
    return os << "BrickName::" << brick_name_to_text.at(name);
}

} // namespace Tetris

#endif
