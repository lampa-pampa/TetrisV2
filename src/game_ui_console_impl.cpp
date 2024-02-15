#include "game_ui_console_impl.h"
#include "pixel.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;

void GameUIConsoleImpl::refresh_board(const vector<vector<Pixel>> &pixels){
    cout << "\e[1;1H\e[2J";
    for(const vector<Pixel> &row : pixels)
    {
        for(const Pixel &pixel: row)
            cout << (pixel.empty() ? "--" : "[]");
        cout << '\n';
    }
}

void GameUIConsoleImpl::refresh_score(int score){}

void GameUIConsoleImpl::refresh_tetrises(int tetrises){}

void GameUIConsoleImpl::refresh_next(const Brick &brick){}

void GameUIConsoleImpl::refresh_hold(const Brick &brick){}