#ifndef INCLUDE_BAG_H
#define INCLUDE_BAG_H

#include "rng.h"
#include <vector>
#include <boost/range/irange.hpp>

namespace Tetris
{

template<typename T>
class Bag final
{
    std::vector<T> items;
    int current_index;
    Rng& rng;

    void shuffle_items(std::vector<T>& items, Rng& rng)
    {
        for (const auto& i : boost::irange<int>(items.size() - 1, 0, -1))
            std::swap(items[i], items[rng.random(i + 1)]);
    }

public:
    Bag(const std::vector<T>& items, Rng& rng)
    :
        items{items},
        current_index{0},
        rng{rng}
    {}
    
    T get_next();
};

template<typename T>
T Bag<T>::get_next()
{
    if (this->current_index == 0)
        this->shuffle_items(this->items, this->rng);
    T item{this->items[this->current_index]};
    this->current_index = (this->current_index + 1) % this->items.size();
    return item; 
}

}

#endif