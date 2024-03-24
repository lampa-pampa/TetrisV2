#include "timer_impl.h"

#include <cmath>
#include <chrono>

using std::pow;
using std::chrono::system_clock;

namespace Tetris
{

TimerImpl::TimerImpl(int start_level)
:
    timeout_time_{Nanoseconds::zero()}
{
    set_timeout_delay(start_level);
}

void TimerImpl::update_time()
{
    const auto cur_time{system_clock::now()};
    const auto duration{cur_time - start_time_};
    time_elapsed(duration);
};

//--------------------------------------------------------

TimerImpl::Nanoseconds TimerImpl::compute_timeout_delay(int level) const
{
    return Nanoseconds{
        static_cast<unsigned long long>(
            pow((0.8 - (level - 1) * 0.007), level - 1) * 1'000'000'000)
    };
}

void TimerImpl::time_elapsed(Nanoseconds time)
{
    timeout_time_ += time;
    if (timeout_time_ >= timeout_delay_)
    {
        timeout_time_ -= timeout_delay_;
        timeout_();
    }
    update_start_time();
}

}