//
// Created by p00ri on 27/01/2023.
//
#include <stdexcept>
#include "Window/Window.h"
#include "Piece.h"
#include "SDL2/SDL_image.h"


Window::Window() {
    window_ = SDL_CreateWindow("Chess",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               800, 600, 0);
    if(window_ == nullptr) throw runtime_error(string("SDL Error : ") + SDL_GetError());

    win_surface_ = SDL_GetWindowSurface(window_);
    if(win_surface_ == nullptr) throw runtime_error(string("SDL Error : ") + SDL_GetError());

    render_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if(render_ == nullptr) throw runtime_error(string("SDL Error : ") + SDL_GetError());

    SDL_SetRenderDrawColor(render_, 0xF0, 0x00, 0x00, 0x00);
    SDL_SetRenderDrawBlendMode(render_, SDL_BLENDMODE_NONE);

    white_pieces_ = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    white_pieces_.at(BISHOP) = loadImg("../assets/chessSet/w_bishop.png");
    white_pieces_.at(KING) = loadImg("../assets/chessSet/w_king.png");
    white_pieces_.at(PAWN) = loadImg("../assets/chessSet/w_pawn.png");
    white_pieces_.at(KNIGHT) = loadImg("../assets/chessSet/w_knight.png");
    white_pieces_.at(QUEEN) = loadImg("../assets/chessSet/w_queen.png");;
    white_pieces_.at(ROOK) = loadImg("../assets/chessSet/w_rook.png");
    black_pieces_ = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    black_pieces_.at(BISHOP) = loadImg("../assets/chessSet/b_bishop.png");
    black_pieces_.at(KING) = loadImg("../assets/chessSet/b_king.png");
    black_pieces_.at(PAWN) = loadImg("../assets/chessSet/b_pawn.png");
    black_pieces_.at(KNIGHT) = loadImg("../assets/chessSet/b_knight.png");
    black_pieces_.at(QUEEN) = loadImg("../assets/chessSet/b_queen.png");
    black_pieces_.at(ROOK) = loadImg("../assets/chessSet/b_rook.png");

    letters_ = {
            loadImg("../assets/char/A.png"),
            loadImg("../assets/char/B.png"),
            loadImg("../assets/char/C.png"),
            loadImg("../assets/char/D.png"),
            loadImg("../assets/char/E.png"),
            loadImg("../assets/char/F.png"),
            loadImg("../assets/char/G.png"),
            loadImg("../assets/char/H.png")
    };

    numbers_ = {
            loadImg("../assets/char/1.png"),
            loadImg("../assets/char/2.png"),
            loadImg("../assets/char/3.png"),
            loadImg("../assets/char/4.png"),
            loadImg("../assets/char/5.png"),
            loadImg("../assets/char/6.png"),
            loadImg("../assets/char/7.png"),
            loadImg("../assets/char/8.png")
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

SDL_Texture* Window::loadImg(const string path_to_file) {

    SDL_Surface* tmp = IMG_Load(path_to_file.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(render_, tmp);
    SDL_FreeSurface(tmp);

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
