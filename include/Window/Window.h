//
// Created by p00ri on 27/01/2023.
//
#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <vector>

using namespace std;

class Window {
private:
    SDL_Window* window_;
    SDL_Surface* win_surface_;
    SDL_Renderer* render_;
    vector<SDL_Texture*> white_pieces_, black_pieces_, letters_, numbers_;

    Window();
public:
    Window(Window& handler)= delete;
    Window& operator=(Window const& ev) = delete;
    ~Window();

    static Window* getMainWindow() {
        static Window window;

        return &window;
    }
    SDL_Window *getWindow() const;
    SDL_Surface *getWinSurface() const;
    SDL_Renderer *getRender() const;

    SDL_Texture * loadPng(string path_to_file);

    const vector<SDL_Texture *> &getWhitePieces() const;

    const vector<SDL_Texture *> &getBlackPieces() const;

    const vector<SDL_Texture *> &getLetters() const;

    const vector<SDL_Texture *> &getNumbers() const;
};
