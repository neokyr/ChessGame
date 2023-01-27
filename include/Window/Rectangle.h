//
// Created by p00ri on 26/01/2023.
//
#pragma once
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

class Rectangle {
private:
    SDL_Rect position_;
public:
    Rectangle(int x, int y, int w, int h);

    bool is_inside(int x, int y);

    SDL_Rect * getPosition();

};
