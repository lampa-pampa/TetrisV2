#ifndef INCLUDE_TIMER_IMPL_H
#define INCLUDE_TIMER_IMPL_H

#include "timer.h"

#include <boost/signals2.hpp>
#include <chrono>
#include <functional>

namespace Tetris
{

class TimerImpl final: public Timer
{  
public:
    TimerImpl();

    void update_time() override;

    void start() override
    {
        this->update_start_time();
        this->active = true;
    }

    void stop() override
    {
        this->active = false;
    }

    void reset_timeout() override
    {
        this->timeout_time = Nanoseconds::zero();
    }

    void set_timeout_delay(int level) override
    {
        this->timeout_delay = this->compute_timeout_delay(level);
    }

    void connect_timeout(const std::function<void()>& handler) override
    {
        this->timeout_signal.connect(handler);
    }

    bool is_active() const override
    {
        return this->active;
    }

private:
    using Signal = boost::signals2::signal<void()>;
    using Nanoseconds = std::chrono::nanoseconds;
    using TimePoint = std::chrono::time_point<
        std::chrono::system_clock, Nanoseconds>;

    Nanoseconds timeout_delay;
    Nanoseconds timeout_time;
    bool active;
    Signal timeout_signal;
    TimePoint start_time;

    Nanoseconds compute_timeout_delay(int level) const;
    void time_elapsed(Nanoseconds time);

    void update_start_time()
    {
        this->start_time = std::chrono::system_clock::now();
    }
};

}

#endif