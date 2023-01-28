//
// Created by p00ri on 28/01/2023.
//
#pragma once

#include "Widget.h"
#include <string>

using namespace std;

class ScrollableWidget : public Widget {
private:
    SDL_Rect surface_size_;
    SDL_Surface* full_surface_;
    SDL_Texture* render_texture_, *background_;
    SDL_Rect viewport_;
    int padding_;

protected:
    SDL_Surface* getSurface();

public:
    ScrollableWidget(int x, int y, int w, int h, string bg_path, int padding);
    ~ScrollableWidget();

    void handleEvent(SDL_Event &e) override;
    void print() final;
};
