#include "config/keyboard/led/filled_config.h"

#include "config/keyboard/led/config.h"

namespace Tetris::Ui
{

const KeyboardConfig keyboard_config{
    {
        // ROW PINS
        2,
        9,
        10,
        15,
    },
    {
        // COLUMN PINS
        21,
        22,
        23,
        32,
    },
    {
        // KEY POSITION TO KEY CODE
        {13, 10},
        {14, '/'},
        {15, '*'},
        {4, '-'},
        {1, '7'},
        {2, '8'},
        {3, '9'},
        {5, '4'},
        {6, '5'},
        {7, '6'},
        {9, '1'},
        {10, '2'},
        {11, '3'},
    },
    -1, // no key code
};

}
