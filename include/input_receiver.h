#ifndef INPUT_RECIEVER_H
#define INPUT_RECIEVER_H

#include <functional>

class InputReceiver
{
    public:
        virtual void connect_move_left_pressed(const std::function<void()> handler) = 0;
        virtual void connect_move_right_pressed(const std::function<void()> handler) = 0;
        virtual void connect_rotate_pressed(const std::function<void()> handler) = 0;
        virtual void connect_soft_drop_pressed(const std::function<void()> handler) = 0;
        virtual void connect_hard_drop_pressed(const std::function<void()> handler) = 0;
        virtual void connect_hold_pressed(const std::function<void()> handler) = 0;
        virtual void connect_pause_pressed(const std::function<void()> handler) = 0;
        virtual ~InputReceiver() = default;
};

#endif