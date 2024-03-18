#ifndef INCLUDE_BAG_H
#define INCLUDE_BAG_H

#include <cstdint>
#include <initializer_list>
#include <vector>

#include <boost/range/irange.hpp>

#include "brick.h"
#include "rng.h"

namespace Tetris
{

template<typename T>
class Bag final
{
public:
    Bag(const std::vector<T>& items, Rng& rng);
    
    T get_next();
    
private:
    int current_index;
    Rng& rng;
    std::vector<T> items;

    void shuffle_items(std::vector<T>& items, Rng& rng)
    {
        for (const auto& i : boost::irange<int>(items.size() - 1, 0, -1))
            std::swap(items[i], items[rng.random(i + 1)]);
    }
};

template<typename T>
Bag<T>::Bag(const std::vector<T>& items, Rng& rng)
:
    items{items},
    current_index{0},
    rng{rng}
{}

explicit Bag(std::initializer_list<Brick>, Rng& rng) -> Bag<Brick>;
explicit Bag(std::initializer_list<uint_fast8_t>, Rng& rng)
    -> Bag<uint_fast8_t>;

template<typename T>
T Bag<T>::get_next()
{
    if (this->current_index == 0)
        this->shuffle_items(this->items, this->rng);
    const T item{this->items[this->current_index]};
    this->current_index = (this->current_index + 1) % this->items.size();
    return item;
}

}

#endif