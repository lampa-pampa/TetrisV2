#include "game_ui_console_impl.h"
#include "pixel.h"
#include <ostream>
#include <vector>
#include <iostream>
#include <string>
#include <functional>

using std::vector;
using std::cout;
using std::string;
using std::flush;
using std::function;

void GameUIConsoleImpl::refresh_board(const vector<vector<Pixel>> &pixels){
    cout << "\e[1;1H\e[2J";
    for(const vector<Pixel> &row : pixels)
    {
        for(const Pixel &pixel: row)
        {
            string pixel_text{"--"};
            if(!pixel.empty())
            {
                if(pixel.is_ghost)
                    pixel_text = "::";
                else
                    pixel_text = "[]";
            }
            cout << pixel_text;
        }
        cout << '\n';
    }
    cout << flush;
}

void GameUIConsoleImpl::refresh_score(int score){}

void GameUIConsoleImpl::refresh_tetrises(int tetrises){}

void GameUIConsoleImpl::refresh_next(const Brick &brick){}

void GameUIConsoleImpl::refresh_hold(const Brick &brick){}

void GameUIConsoleImpl::connect_move_left_pressed(function<void()> handler)
{
    this->move_left_pressed.connect(handler);
}

void GameUIConsoleImpl::connect_move_right_pressed(function<void()> handler)
{
    this->move_right_pressed.connect(handler);
}

void GameUIConsoleImpl::connect_rotate_pressed(function<void()> handler)
{
    this->rotate_pressed.connect(handler);
}

void GameUIConsoleImpl::connect_soft_drop_pressed(function<void()> handler)
{
    this->soft_drop_pressed.connect(handler);
}

void GameUIConsoleImpl::connect_hard_drop_pressed(function<void()> handler)
{
    this->hard_drop_pressed.connect(handler);
}

void GameUIConsoleImpl::connect_hold_pressed(function<void()> handler)
{
    this->hold_pressed.connect(handler);
}

void GameUIConsoleImpl::connect_pause_pressed(function<void()> handler)
{
    this->pause_pressed.connect(handler);
}