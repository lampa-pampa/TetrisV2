#ifndef TEST_BRICKS_H
#define TEST_BRICKS_H

#include "pixel.h"
#include "color.h"
#include <map>
#include <vector>

const std::map<char, std::vector<Pixel>> test_pixel_lists{
    {'I', {
        {{-1, 0}, Color::blue},
        {{0, 0}, Color::blue},
        {{1, 0}, Color::blue},
        {{2, 0}, Color::blue},
    }},
    {'O', {
        {{0, 0}, Color::blue},
        {{1, 0}, Color::blue},
        {{0, 1}, Color::blue},
        {{1, 1}, Color::blue},
    }},
    {'T', {
        {{-1, 0}, Color::blue},
        {{0, 0}, Color::blue},
        {{1, 0}, Color::blue},
        {{0, 1}, Color::blue},
    }},
    {'J', {
        {{0, -1}, Color::blue},
        {{0, 0}, Color::blue},
        {{-1, 1}, Color::blue},
        {{0, 1}, Color::blue},
    }},
    {'L', {
        {{0, -1}, Color::blue},
        {{0, 0}, Color::blue},
        {{0, 1}, Color::blue},
        {{1, 1}, Color::blue},
    }},
    {'Z', {
        {{-1, -1}, Color::blue},
        {{0, -1}, Color::blue},
        {{0, 0}, Color::blue},
        {{1, 0}, Color::blue},
    }},
    {'S', {
        {{-1, 1}, Color::blue},
        {{0, -1}, Color::blue},
        {{0, 0}, Color::blue},
        {{-1, 0}, Color::blue},
    }},
};

#endif