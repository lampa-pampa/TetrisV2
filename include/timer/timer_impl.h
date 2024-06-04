#ifndef INCLUDE_TIMER_IMPL_H
#define INCLUDE_TIMER_IMPL_H

#undef timeout

#include "timer/timer.h"

#include <boost/signals2.hpp>
#include <functional>

namespace Tetris
{

class TimerImpl final: public Timer
{
public:
    TimerImpl(int start_level): timeout_time_{}
    {
        set_timeout_delay(start_level);
        start();
    }

    void start() override
    {
        active_ = true;
    }

    void stop() override
    {
        active_ = false;
    }

    void reset_timeout() override
    {
        timeout_time_ = 0;
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

    void update(unsigned long delta_time) override;

private:
    using Signal = boost::signals2::signal<void()>;

    unsigned long timeout_delay_;
    unsigned long timeout_time_;
    bool active_;
    Signal timeout_;

    unsigned long compute_timeout_delay(int level) const;
};

} // namespace Tetris

#endif
