
#include "Window/ScrollableWidget.h"
#include "Window/Window.h"
#include <stdexcept>

using namespace std;

ScrollableWidget::ScrollableWidget(int x, int y, int w, int h, string bg_path = "", int padding = 0) :
    Widget(x, y, w, h) {
    Window *win = Window::getMainWindow();
    EventHandler *handler = EventHandler::getEventHandler();

    handler->subscribe(this);

    if(!bg_path.empty()) {
        if(padding >= w/2 || padding >= h/2 || padding < 0) throw invalid_argument("incorrect padding");
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

        Sint32 x = e.wheel.x * WHEEL_SPEED;
        Sint32 y = e.wheel.y * -WHEEL_SPEED;
        
        if(viewport_.x + x < 0){
            viewport_.x = 0;
        } else if (viewport_.x + viewport_.w + x > surface_size_.w) {
            viewport_.x = surface_size_.w - viewport_.w;
        } else {
            viewport_.x += x;
        }

        
        if(viewport_.y + y < 0){
            viewport_.y = 0;
        } else if (viewport_.y + viewport_.h + y > surface_size_.h) {
            viewport_.y = surface_size_.h - viewport_.h;
        } else {
            viewport_.y += y;
        }
        
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

    SDL_UpdateTexture(render_texture_, &full_surface_->clip_rect, full_surface_->pixels, full_surface_->pitch);
    SDL_RenderCopy(win->getRender(), render_texture_, &viewport_, &vpPosition);

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

void ScrollableWidget::setSurface(SDL_Surface *new_surface) {
    Window* win = Window::getMainWindow();
    if(full_surface_ != nullptr) SDL_FreeSurface(full_surface_);
    full_surface_ = new_surface;
    surface_size_ = full_surface_->clip_rect;
    render_texture_ = SDL_CreateTextureFromSurface(win->getRender(), full_surface_);
}

