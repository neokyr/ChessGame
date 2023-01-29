//
// Created by p00ri on 28/01/2023.
//

#include "Window/ScrollableWidget.h"
#include "Window/Window.h"
#include <stdexcept>

using namespace std;

ScrollableWidget::ScrollableWidget(int x, int y, int w, int h, string bg_path = "", int padding = 0) :
    Widget(x, y, w, h) {
    Window *win = Window::getMainWindow();

    if(!bg_path.empty()) {
        if(padding >= w/2 || padding >= h/2) throw invalid_argument("incorrect padding");
        padding_ = padding;
        background_ = win->loadImg(bg_path);
        viewport_ = {0, 0, w -padding_*2, h -padding_ * 2};
    } else {
        padding_ = 0;
        background_ = nullptr;
        viewport_ = {0, 0, w, h};
    }

    full_surface_ = SDL_CreateRGBSurface(0, 0, 0, 32, 0, 0, 0, 0);
    surface_size_ = full_surface_->clip_rect;
    render_texture_ = SDL_CreateTextureFromSurface(win->getRender(), full_surface_);


}


void ScrollableWidget::handleEvent(SDL_Event &e) {
    if(e.type == SDL_MOUSEWHEEL && is_inside(e.wheel.mouseX, e.wheel.mouseY)) {
        if(viewport_.x + e.wheel.x >= 0 && viewport_.x + viewport_.w + e.wheel.x <= surface_size_.w)
            viewport_.x += e.wheel.x;

        if(viewport_.y + e.wheel.y >= 0 && viewport_.y + viewport_.h + e.wheel.y <= surface_size_.y)
            viewport_.y += e.wheel.y;
    }
}

void ScrollableWidget::print() {
    Window *win = Window::getMainWindow();
    SDL_Rect vpPosition = *getPosition();

    if (background_ != nullptr) {
        SDL_RenderCopy(win->getRender(), background_, nullptr, getPosition());
        vpPosition.x += padding_;
        vpPosition.y += padding_;
        vpPosition.w -= padding_ * 2;
        vpPosition.h -= padding_ * 2;
    }

    SDL_UpdateTexture(render_texture_, &viewport_, full_surface_->pixels, full_surface_->pitch);
    SDL_RenderCopy(win->getRender(), render_texture_, nullptr, &vpPosition);

}

ScrollableWidget::~ScrollableWidget() {
    SDL_DestroyTexture(render_texture_);
    if(background_ != nullptr) {
        SDL_DestroyTexture(background_);
    }
    SDL_FreeSurface(full_surface_);
}

SDL_Surface *ScrollableWidget::getSurface() {
    return full_surface_;
}

