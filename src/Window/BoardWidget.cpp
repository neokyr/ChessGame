//
// Created by Formation on 27/01/2023.
//
#include "Window/BoardWidget.h"
#include "Window/Window.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wwritable-strings"
BoardWidget::BoardWidget(int x, int y, int w/*, Board& board, Game& game*/):
    Widget(x, y, w, w)/*, board_(board), game_(game) */ {
    Window *win = Window::getMainWindow();

    w_case_0_ = win->loadPng("../assets/chessSet/square_gray_light.png");
    w_case_1_ = win->loadPng("../assets/chessSet/square_gray_dark.png");
    b_case_0_ = win->loadPng("../assets/chessSet/square_brown_light.png");
    b_case_1_ = win->loadPng("../assets/chessSet/square_brown_dark.png");
    w_bishop_ = win->loadPng("../assets/chessSet/w_bishop.png");
    w_king_ = win->loadPng("../assets/chessSet/w_king.png");
    w_knight_ = win->loadPng("../assets/chessSet/w_knight.png");
    w_pawn_ = win->loadPng("../assets/chessSet/w_pawn.png");
    w_queen_ = win->loadPng("../assets/chessSet/w_queen.png");
    w_rook_ = win->loadPng("../assets/chessSet/w_rook.png");
    b_bishop_ = win->loadPng("../assets/chessSet/b_bishop.png");
    b_king_ = win->loadPng("../assets/chessSet/b_king.png");
    b_knight_ = win->loadPng("../assets/chessSet/b_knight.png");
    b_pawn_ = win->loadPng("../assets/chessSet/b_pawn.png");
    b_queen_ = win->loadPng("../assets/chessSet/b_queen.png");
    b_rook_ = win->loadPng("../assets/chessSet/b_rook.png");
    letters = {
            win->loadPng("../assets/char/A.png"),
            win->loadPng("../assets/char/B.png"),
            win->loadPng("../assets/char/C.png"),
            win->loadPng("../assets/char/D.png"),
            win->loadPng("../assets/char/E.png"),
            win->loadPng("../assets/char/F.png"),
            win->loadPng("../assets/char/G.png"),
            win->loadPng("../assets/char/H.png")
    };

    numbers_ = {
            win->loadPng("../assets/char/1.png"),
            win->loadPng("../assets/char/2.png"),
            win->loadPng("../assets/char/3.png"),
            win->loadPng("../assets/char/4.png"),
            win->loadPng("../assets/char/5.png"),
            win->loadPng("../assets/char/6.png"),
            win->loadPng("../assets/char/7.png"),
            win->loadPng("../assets/char/8.png")
    };


}

void BoardWidget::handleEvent(SDL_Event &e) {

}

void BoardWidget::print() {
    Window *win = Window::getMainWindow();
    SDL_Rect* board =  getPosition();
    int w = (board->w) /9;
    int h = (board->h) /9;

    for (int i = 7 ; i >= 0; i--) {
        int y = (7-i) * h;
        int x = 0 + w*0.1;
        SDL_Rect r = {x,y,(int) (w * 0.8), h};
        SDL_RenderCopy(win->getRender(), letters[i], nullptr, &r);
    }

    for (int i = 0 ; i < 8; i++) {
        int y = board->h - h;
        int x = i * w + w + w *0.2;
        SDL_Rect r = {x,y,(int) (w *0.8),h };
        SDL_RenderCopy(win->getRender(), numbers_[i], nullptr, &r);
    }

    for (int i = 0; i <64; ++i) {
        bool is_white_case = (i%2 + i/8) %2;
        int x = (i%8) * w + w;
        int y = (i/8) * h;
        SDL_Rect r = {x,y,w,h};
        if(is_white_case) {
            SDL_RenderCopy(win->getRender(), w_case_0_, nullptr, &r);
        } else {
            SDL_RenderCopy(win->getRender(), b_case_0_, nullptr, &r);
        }
        /* TODO Add pieces */
    }
}


#pragma clang diagnostic pop