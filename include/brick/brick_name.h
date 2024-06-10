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
    o,
    i,
    z,
    s,
    t,
    l,
    j,
};

const std::map<BrickName, std::string> brick_name_to_text{
    {BrickName::empty, "empty"},
    {BrickName::o, "o"},
    {BrickName::i, "i"},
    {BrickName::z, "z"},
    {BrickName::s, "s"},
    {BrickName::t, "t"},
    {BrickName::l, "j"},
    {BrickName::j, "l"},
};

inline std::ostream& operator<<(std::ostream& os, BrickName name)
{
    return os << "BrickName::" << brick_name_to_text.at(name);
}

} // namespace Tetris

#endif
