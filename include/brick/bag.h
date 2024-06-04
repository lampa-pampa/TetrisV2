#ifndef INCLUDE_BAG_H
#define INCLUDE_BAG_H

#include <cstdint>
#include <initializer_list>
#include <vector>

#include <boost/range/irange.hpp>

#include "brick/brick.h"
#include "rng/rng.h"

namespace Tetris
{

template<typename T>
class Bag final
{
public:
    Bag(const std::vector<T>& items, Rng& rng);

    T get_next();

private:
    int current_index_;
    Rng& rng_;
    std::vector<T> items_;

    void shuffle_items()
    {
        for (const auto& i : boost::irange<int>(items_.size() - 1, 0, -1))
            std::swap(items_[i], items_[rng_.random(i + 1)]);
    }
};

template<typename T>
Bag<T>::Bag(const std::vector<T>& items, Rng& rng)
  : items_{items},
    current_index_{},
    rng_{rng}
{}

explicit Bag(std::initializer_list<Brick>, Rng& rng) -> Bag<Brick>;
explicit Bag(
    std::initializer_list<uint_fast8_t>, Rng& rng) -> Bag<uint_fast8_t>;

template<typename T>
T Bag<T>::get_next()
{
    if (current_index_ == 0)
        shuffle_items();
    const T item{items_[current_index_]};
    current_index_ = (current_index_ + 1) % items_.size();
    return item;
}

} // namespace Tetris

#endif
