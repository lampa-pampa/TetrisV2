#ifndef INCLUDE_TIMER_IMPL_H
#define INCLUDE_TIMER_IMPL_H

#undef timeout

#include "timer.h"

#include <boost/signals2.hpp>
#include <chrono>
#include <functional>

namespace Tetris
{

class TimerImpl final: public Timer
{  
public:
    TimerImpl(int start_level);

    void update_time() override;

    void start() override
    {
        update_start_time();
        active_ = true;
    }

    void stop() override
    {
        active_ = false;
    }

    void reset_timeout() override
    {
        timeout_time_ = Nanoseconds::zero();
    }

    void set_timeout_delay(int level) override
    {
        timeout_delay_ = compute_timeout_delay(level);
    }

    void connect_timeout(const std::function<void()>& handler) override
    {
        timeout_.connect(handler);
    }

    bool is_active() const override
    {
        return active_;
    }

private:
    using Signal = boost::signals2::signal<void()>;
    using Nanoseconds = std::chrono::nanoseconds;
    using TimePoint = std::chrono::time_point<
        std::chrono::system_clock, Nanoseconds>;

    Nanoseconds timeout_delay_;
    Nanoseconds timeout_time_;
    bool active_;
    Signal timeout_;
    TimePoint start_time_;

    Nanoseconds compute_timeout_delay(int level) const;
    void time_elapsed(Nanoseconds time);

    void update_start_time()
    {
        start_time_ = std::chrono::system_clock::now();
    }
};

}

#endif