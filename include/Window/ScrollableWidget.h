//
// Created by p00ri on 28/01/2023.
//
#pragma once

#include "Widget.h"
#include <string>

using namespace std;

class ScrollableWidget : public Widget {
private:
    static const int WHEEL_SPEED =5;
    SDL_Rect surface_size_{0,0,0,0};
    SDL_Texture* render_texture_{}, *background_;
    SDL_Rect viewport_{0,0,0,0};
    int padding_;

protected:
    void setRenderTexture(SDL_Texture *renderTexture);
public:
    int getPadding() const;

    ScrollableWidget(int x, int y, int w, int h, string bg_path, int padding);
    ~ScrollableWidget();

    void handleEvent(SDL_Event &e) override;
    void print() override;

};
