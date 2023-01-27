//
// Created by p00ri on 26/01/2023.
//
#pragma once
#include "EventHandler.h"
#include "Widget.h"
#include <string>
#include <functional>

using namespace std;

class Button : public Widget{
private:
    SDL_Texture *button_up_{}, *button_down_{};
    std::function<void ()> clickCallback_;
    bool is_down;
public:
    Button(int x, int y, int w, int h, char *btn_up_path, char *btn_down_path, std::function<void (void)> clickCallback);
    void print() override;
    void handleEvent(SDL_Event &e) override;

};
