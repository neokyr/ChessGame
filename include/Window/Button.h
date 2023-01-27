//
// Created by p00ri on 26/01/2023.
//
#pragma once
#include "EventHandler.h"
#include "Rectangle.h"
#include <string>

using namespace std;

class Button : public Event, public Rectangle{
private:
    SDL_Texture *button_up_{}, *button_down_{};
    void (*clickCallback_)();
    bool is_down;
public:
    Button(int x, int y, int w, int h, string btn_up_path, string btn_down_path, void (*clickCallback)());
    void print();
    void handleEvent(SDL_Event &e) override;

};
