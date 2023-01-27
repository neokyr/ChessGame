//
// Created by p00ri on 27/01/2023.
//
#pragma once
#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Window {
private:
    SDL_Window* window_;
    SDL_Surface* win_surface_;
    SDL_Renderer* render_;

    Window();
public:
    Window(Window& handler)= delete;
    Window& operator=(Window const& ev) = delete;

    static Window* getMainWindow() {
        static Window window;

        return &window;
    }
    SDL_Window *getWindow() const;
    SDL_Surface *getWinSurface() const;
    SDL_Renderer *getRender() const;

    SDL_Texture * loadPng(char* path_to_file);
};
