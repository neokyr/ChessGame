//
// Created by p00ri on 27/01/2023.
//
#include <stdexcept>
#include "Window/Window.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Window/stb_image.h"


Window::Window() {
    window_ = SDL_CreateWindow("Chess",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               800, 800, 0);

    win_surface_ = SDL_GetWindowSurface(window_);

    render_ = SDL_CreateRenderer(window_, -1, 0);

    SDL_SetRenderDrawColor(render_, 0x00, 0xFF, 0x22, 0x00);
}

SDL_Window *Window::getWindow() const {
    return window_;
}

SDL_Surface *Window::getWinSurface() const {
    return win_surface_;
}

SDL_Renderer *Window::getRender() const {
    return render_;
}

SDL_Texture* Window::loadingPng(char *path_to_file) {
    int width, height, channels;
    unsigned char* imageData = stbi_load(path_to_file, &width, &height, &channels, STBI_rgb_alpha);
    if (!imageData) {
        throw invalid_argument(string("error loading image: ") + stbi_failure_reason());
    }

    SDL_Texture* texture = SDL_CreateTexture(render_, SDL_PIXELFORMAT_BGRA8888, SDL_TEXTUREACCESS_STATIC, width, height);
    if (!texture) {
        throw invalid_argument(string("error creating texture: ") + SDL_GetError());
    }
    SDL_UpdateTexture(texture, nullptr, imageData, width * sizeof(Uint32));

    return texture;
}
