#ifndef INCLUDE_SETTINGS_H
#define INCLUDE_SETTINGS_H

#include <ios>
#include <ostream>

namespace Tetris
{

struct Settings final
{
    bool generate_ghost;

    bool operator==(const Settings& other) const
    {
        return this->generate_ghost == other.generate_ghost;
    }

    friend inline std::ostream& operator<<(std::ostream& os,
        const Settings& settings)
    {
        return os << "{" << std::boolalpha << settings.generate_ghost << "}";
    }
};

}

#endif