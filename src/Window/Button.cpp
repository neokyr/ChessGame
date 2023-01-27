//
// Created by p00ri on 26/01/2023.
//
#include "../../include/Window/Button.h"
#include "Window/Window.h"

Button::Button(int x, int y, int w, int h, char *btn_up_path, char *btn_down_path, void (*clickCallback)()) :
        Widget(x, y, w, h), is_down(false), clickCallback_(clickCallback) {

    button_up_ = Window::getMainWindow()->loadPng(btn_up_path);
    button_down_ = Window::getMainWindow()->loadPng(btn_down_path);
    EventHandler::getEventHandler()->subscribe(this);
}

void Button::print() {
    Window* w = Window::getMainWindow();
    if(is_down) {
        SDL_RenderCopy(w->getRender(), button_down_, nullptr, getPosition());
    } else {
        SDL_RenderCopy(w->getRender(), button_up_, nullptr, getPosition());
    }
}

void Button::handleEvent(SDL_Event &e) {
    if(e.type == SDL_MOUSEBUTTONDOWN && is_inside(e.button.x, e.button.y)) {
        is_down = true;
    } else if(e.type == SDL_MOUSEBUTTONUP && is_down) {
        is_down = false;
        if(is_inside(e.button.x, e.button.y)) {
            clickCallback_();
        }
    }
}
