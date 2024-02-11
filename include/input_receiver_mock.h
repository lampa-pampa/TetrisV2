#ifndef INPUT_RECIEVER_MOCK_H
#define INPUT_RECIEVER_MOCK_H

#include "input_receiver.h"
#include <boost/signals2.hpp>
#include <functional>

class InputReceiverMock: public InputReceiver
{
    boost::signals2::signal<void()> move_left_pressed;
    boost::signals2::signal<void()> move_right_pressed;
    boost::signals2::signal<void()> rotate_pressed;
    boost::signals2::signal<void()> soft_drop_pressed;
    boost::signals2::signal<void()> hard_drop_pressed;
    boost::signals2::signal<void()> hold_pressed;
    boost::signals2::signal<void()> pause_pressed;

    public:
        void connect_move_left_pressed(const std::function<void()> handler) override;
        void connect_move_right_pressed(const std::function<void()> handler) override;
        void connect_rotate_pressed(const std::function<void()> handler) override;
        void connect_soft_drop_pressed(const std::function<void()> handler) override;
        void connect_hard_drop_pressed(const std::function<void()> handler) override;
        void connect_hold_pressed(const std::function<void()> handler) override;
        void connect_pause_pressed(const std::function<void()> handler) override;
        void simulate_move_left_pressed(int times = 1) const;
        void simulate_move_right_pressed(int times = 1) const;
        void simulate_rotate_pressed(int times = 1) const;
        void simulate_soft_drop_pressed(int times = 1) const;
        void simulate_hard_drop_pressed(int times = 1) const;
        void simulate_hold_pressed(int times = 1) const;
        void simulate_pause_pressed(int times = 1) const;

};

#endif