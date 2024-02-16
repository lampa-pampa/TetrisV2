#include "game_ui_console_impl.h"
#include "pixel.h"
#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::cout;
using std::string;

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
}

void GameUIConsoleImpl::refresh_score(int score){}

void GameUIConsoleImpl::refresh_tetrises(int tetrises){}

void GameUIConsoleImpl::refresh_next(const Brick &brick){}

void GameUIConsoleImpl::refresh_hold(const Brick &brick){}