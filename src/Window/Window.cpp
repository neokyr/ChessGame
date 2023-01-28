//
// Created by p00ri on 27/01/2023.
//
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wwritable-strings"

#include <stdexcept>
#include "Window/Window.h"
#include "Piece.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Window/stb_image.h"


Window::Window() {
    window_ = SDL_CreateWindow("Chess",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               800, 600, 0);

    win_surface_ = SDL_GetWindowSurface(window_);
    render_ = SDL_CreateRenderer(window_, -1, 0);
    SDL_SetRenderDrawColor(render_, 0x00, 0x00, 0x00, 0x00);

    white_pieces_ = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    white_pieces_.at(BISHOP) = loadPng("../assets/chessSet/w_bishop.png");
    white_pieces_.at(KING) =   loadPng("../assets/chessSet/w_king.png");
    white_pieces_.at(PAWN) =   loadPng("../assets/chessSet/w_pawn.png");
    white_pieces_.at(KNIGHT) = loadPng("../assets/chessSet/w_knight.png");
    white_pieces_.at(QUEEN) =  loadPng("../assets/chessSet/w_queen.png");;
    white_pieces_.at(ROOK) =   loadPng("../assets/chessSet/w_rook.png");
    black_pieces_ = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    black_pieces_.at(BISHOP) = loadPng("../assets/chessSet/b_bishop.png");
    black_pieces_.at(KING) =   loadPng("../assets/chessSet/b_king.png");
    black_pieces_.at(PAWN) =   loadPng("../assets/chessSet/b_pawn.png");
    black_pieces_.at(KNIGHT) = loadPng("../assets/chessSet/b_knight.png");
    black_pieces_.at(QUEEN) =  loadPng("../assets/chessSet/b_queen.png");
    black_pieces_.at(ROOK) =   loadPng("../assets/chessSet/b_rook.png");

    letters_ = {
            loadPng("../assets/char/A.png"),
            loadPng("../assets/char/B.png"),
            loadPng("../assets/char/C.png"),
            loadPng("../assets/char/D.png"),
            loadPng("../assets/char/E.png"),
            loadPng("../assets/char/F.png"),
            loadPng("../assets/char/G.png"),
            loadPng("../assets/char/H.png")
    };

    numbers_ = {
            loadPng("../assets/char/1.png"),
            loadPng("../assets/char/2.png"),
            loadPng("../assets/char/3.png"),
            loadPng("../assets/char/4.png"),
            loadPng("../assets/char/5.png"),
            loadPng("../assets/char/6.png"),
            loadPng("../assets/char/7.png"),
            loadPng("../assets/char/8.png")
    };


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

SDL_Texture* Window::loadPng(char *path_to_file) {
    int width, height, channels;
    unsigned char* imageData = stbi_load(path_to_file, &width, &height, &channels, STBI_rgb_alpha);
    if (!imageData) {
        throw invalid_argument(string("error loading image: ") + stbi_failure_reason());
    }

    SDL_Texture* texture = SDL_CreateTexture(render_, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, width, height);
    if (!texture) {
        throw invalid_argument(string("error creating texture: ") + SDL_GetError());
    }
    SDL_UpdateTexture(texture, nullptr, imageData, width * sizeof(Uint32));

    return texture;
}

Window::~Window() {
    for(auto& letter : letters_) {
        SDL_DestroyTexture(letter);
    }
    for(auto& number : numbers_) {
        SDL_DestroyTexture(number);
    }
    for(auto& w_piece : white_pieces_) {
        SDL_DestroyTexture(w_piece);
    }
    for(auto& b_piece : black_pieces_) {
        SDL_DestroyTexture(b_piece);
    }
    SDL_DestroyRenderer(render_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

const vector<SDL_Texture *> &Window::getWhitePieces() const {
    return white_pieces_;
}

const vector<SDL_Texture *> &Window::getBlackPieces() const {
    return black_pieces_;
}

const vector<SDL_Texture *> &Window::getLetters() const {
    return letters_;
}

const vector<SDL_Texture *> &Window::getNumbers() const {
    return numbers_;
}

#pragma clang diagnostic pop