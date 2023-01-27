//
// Created by p00ri on 26/01/2023.
//

#include "../../include/Window/Rectangle.h"

Rectangle::Rectangle(int x, int y, int w, int h) :
        position_({x, y, w, h}){}

bool Rectangle::is_inside(int x, int y) {
    bool inx = x >= position_.x && x <= (position_.x + position_.w);
    bool iny = y >= position_.y && y <= (position_.y + position_.h);
    return inx && iny;
}

SDL_Rect* Rectangle::getPosition() {
    return &position_;
}
