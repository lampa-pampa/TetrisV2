#ifndef TIMER_MOCK_H
#define TIMER_MOCK_H

#include "timer.h"
#include <boost/signals2.hpp>
#include <functional>

class TimerMock final: public Timer
{
    boost::signals2::signal<void()> timeout;

    public:
        void start() override{}
        void stop() override{}
        void connect_timeout(const std::function<void()> handler) override{}
};

#endif