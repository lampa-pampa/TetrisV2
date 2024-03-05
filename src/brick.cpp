#include "brick.h"

#include <ostream>

#include <boost/range/irange.hpp>

#include "cube.h"
#include "vector_2.h"

namespace Tetris
{

using std::ostream;

ostream& operator<<(ostream& os, const Brick& brick)
{
    os << "{{ ";
    for (const auto& cube : brick.cubes)
    {
        os << cube;
        if (&cube != &brick.cubes.back())
            os << ", ";
    }
    return os << " }, " << brick.rotation_offset << "}";
}

}