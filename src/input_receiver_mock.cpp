#include "input_receiver_mock.h"
#include <functional>

using std::function;

void InputReceiverMock::connect_move_left_pressed(const function<void()> handler)
{
    this->move_left_pressed.connect(handler);
}

void InputReceiverMock::connect_move_right_pressed(const function<void()> handler)
{
    this->move_right_pressed.connect(handler);
}

void InputReceiverMock::connect_rotate_pressed(const function<void()> handler)
{
    this->rotate_pressed.connect(handler);
}

void InputReceiverMock::connect_soft_drop_pressed(const function<void()> handler)
{
    this->soft_drop_pressed.connect(handler);
}

void InputReceiverMock::connect_hard_drop_pressed(const function<void()> handler)
{
    this->hard_drop_pressed.connect(handler);
}

void InputReceiverMock::connect_hold_pressed(const function<void()> handler)
{
    this->hold_pressed.connect(handler);
}

void InputReceiverMock::connect_pause_pressed(const function<void()> handler)
{
    this->pause_pressed.connect(handler);
}

void InputReceiverMock::simulate_move_left_pressed()
{
    this->move_left_pressed();
}

void InputReceiverMock::simulate_move_right_pressed()
{
    this->move_right_pressed();
}

void InputReceiverMock::simulate_rotate_pressed()
{
    this->rotate_pressed();
}

void InputReceiverMock::simulate_soft_drop_pressed()
{
    this->soft_drop_pressed();
}

void InputReceiverMock::simulate_hard_drop_pressed()
{
    this->hard_drop_pressed();
}

void InputReceiverMock::simulate_hold_pressed()
{
    this->hold_pressed();
}

void InputReceiverMock::simulate_pause_pressed()
{
    this->pause_pressed();
}