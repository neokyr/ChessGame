
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

    //SDL_UpdateTexture(render_texture_, &full_surface_->clip_rect, full_surface_->pixels, full_surface_->pitch);
    SDL_RenderCopy(win->getRender(), render_texture_, &viewport_, &vpPosition);

}

ScrollableWidget::~ScrollableWidget() {
    SDL_DestroyTexture(render_texture_);
    if(background_ != nullptr) {
        SDL_DestroyTexture(background_);
    }
}

int ScrollableWidget::getPadding() const {
    return padding_;
}

void ScrollableWidget::setRenderTexture(SDL_Texture *renderTexture) {
    if(render_texture_ != nullptr) SDL_DestroyTexture(render_texture_);
    render_texture_ = renderTexture;
    int w, h;
    SDL_QueryTexture(render_texture_, nullptr, nullptr, &w, &h);
    surface_size_ = {0 ,0, w, h};
}

