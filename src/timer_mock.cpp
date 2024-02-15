#include "timer_mock.h"
#include <functional>

using std::function;

TimerMock::TimerMock()
:
    active(false)
{}

void TimerMock::start()
{
    this->active = true;
}

void TimerMock::stop()
{
    this->active = false;
}

void TimerMock::simulate_timeout(int times) const
{
    for(int i{0}; i < times; ++i)
        this->timeout();
}

void TimerMock::connect_timeout(function<void()> handler)
{
    this->timeout.connect(handler);
}