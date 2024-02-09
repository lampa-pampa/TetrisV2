#ifndef TIMER_MOCK_H
#define TIMER_MOCK_H

#include "timer.h"
#include <boost/signals2.hpp>
#include <functional>

class TimerMock: public Timer
{
    boost::signals2::signal<void()> timeout;
    int delay_in_ms;
    int step_in_ms;
    bool active;

    public:
        TimerMock(int delay_in_ms, int step_in_ms);
        void start() override;
        void stop() override;
        void tick(int times);
        void connect_timeout(const std::function<void()> handler) override;
};

#endif