#ifndef BAG_H
#define BAG_H

#include "rng.h"
#include <vector>
#include <memory>

template<typename T>
class Bag
{
    std::vector<T> items;
    int current_index;
    std::unique_ptr<RNG> rng;

    void shuffle_items(std::vector<T> &items, std::unique_ptr<RNG> &rng);

    public:
        Bag(std::vector<T> &items, std::unique_ptr<RNG> &&rng);
        Bag(Bag<T> &&other);
        T get_next();
};

template<typename T>
Bag<T>::Bag(std::vector<T> &items, std::unique_ptr<RNG> &&rng)
:
    items(items),
    current_index(0),
    rng(std::move(rng))
{}

template<typename T>
Bag<T>::Bag(Bag<T> &&other)
:
    items(other.items),
    current_index(other.current_index),
    rng(std::move(other.rng))
{
    other.items = std::vector<T>{};
    other.current_index = 0;
    other.rng = nullptr;
}

template<typename T>
void Bag<T>::shuffle_items(std::vector<T> &items, std::unique_ptr<RNG> &rng)
{
    for(int i = items.size() - 1; i >= 0; --i)
        std::swap(items[i], items[rng->random(i + 1)]);
}

template<typename T>
T Bag<T>::get_next()
{
    if(this->current_index == 0)
        this->shuffle_items(this->items, this->rng);
    T item = this->items[this->current_index];
    this->current_index = (this->current_index + 1) % this->items.size();
    return item; 
}

#endif