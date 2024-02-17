#ifndef TIMER_MOCK_H
#define TIMER_MOCK_H

#include "timer.h"
#include <functional>
#include <boost/signals2.hpp>

class TimerMock: public Timer
{
    boost::signals2::signal<void()> timeout;
    bool active;

    public:
        TimerMock();
        void start() override;
        void stop() override;
        void connect_timeout(const std::function<void()> handler) override;
        void simulate_timeout(int times = 1) const;
};

#endif