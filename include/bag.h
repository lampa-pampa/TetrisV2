#ifndef BAG_H
#define BAG_H

#include "rng.h"
#include <vector>
#include <boost/range/irange.hpp>

template<typename T>
class Bag final
{
    std::vector<T> items;
    int current_index;
    RNG& rng;

    void shuffle_items(std::vector<T>& items, RNG& rng);

public:
    Bag(const std::vector<T>& items, RNG& rng);
    T get_next();
};

template<typename T>
Bag<T>::Bag(const std::vector<T>& items, RNG& rng)
:
    items(items),
    current_index(0),
    rng(rng)
{}

template<typename T>
void Bag<T>::shuffle_items(std::vector<T>& items, RNG& rng)
{
    for (const auto& i : boost::irange<size_t>(items.size() - 1, 0, -1))
        std::swap(items[i], items[rng.random(i + 1)]);
}

template<typename T>
T Bag<T>::get_next()
{
    if (this->current_index == 0)
        this->shuffle_items(this->items, this->rng);
    T item{this->items[this->current_index]};
    this->current_index = (this->current_index + 1) % this->items.size();
    return item; 
}

#endif