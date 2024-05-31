#include "timer/timer_impl.h"

#include <cmath>

using std::pow;

namespace Tetris
{

void TimerImpl::update(unsigned long delta_time)
{
    timeout_time_ += delta_time;
    if (timeout_time_ >= timeout_delay_)
    {
        timeout_time_ -= timeout_delay_;
        timeout_();
    }
};

//--------------------------------------------------------

unsigned long TimerImpl::compute_timeout_delay(int level) const
{
    return static_cast<unsigned long>(
        pow((0.8 - (level - 1) * 0.007), level - 1) * 1000);
}

} // namespace Tetris
