
#include "Window/BoardWidget.h"
#include "Window/Window.h"
#include "Piece.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wwritable-strings"
BoardWidget::BoardWidget(int x, int y, int w, Game& game):
    Widget(x, y, w, w), game_(game) {
    Window *win = Window::getMainWindow();

    w_case_0_ = win->loadImg("../assets/chessSet/square_gray_light.png");
    w_case_1_ = win->loadImg("../assets/chessSet/square_gray_dark.png");
    b_case_0_ = win->loadImg("../assets/chessSet/square_brown_light.png");
    b_case_1_ = win->loadImg("../assets/chessSet/square_brown_dark.png");
    letters_ = win->getLetters();
    numbers_ = win->getNumbers();
    w_piece_ = win->getWhitePieces();
    b_piece_ = win->getBlackPieces();


}

void BoardWidget::handleEvent(SDL_Event &e) {

}

void BoardWidget::print() {
    Window *win = Window::getMainWindow();
    SDL_Rect* board =  getPosition();

    int h_font = 30;
    int w_font = (int) (h_font * 0.8);
    int font_space = 40;

    int w_case = (board->w - font_space) / 8;
    int h_case = (board->h - font_space) / 8;

    for (int i = 7 ; i >= 0; i--) {
        int x = board->x + (font_space - w_font) /2;
        int y = board->y + (7-i) * h_case + (h_case - h_font) /2;
        SDL_Rect r = {x, y, w_font, h_font};
        SDL_RenderCopy(win->getRender(), letters_[i], nullptr, &r);
    }

    for (int i = 0 ; i < 8; i++) {
        int x = board->x + i * w_case + font_space + (w_case - w_font) /2;
        int y = board->y + board->h - font_space + (font_space - h_font) /2;
        SDL_Rect r = {x, y, w_font, h_font};
        SDL_RenderCopy(win->getRender(), numbers_[i], nullptr, &r);
    }

    for (int i = 0; i <64; ++i) {
        bool is_white_case = (i%2 + i/8) %2;
        int x = (i%8) * w_case + font_space + board->x;
        int y = (i/8) * h_case + board->y;
        SDL_Rect r = {x, y, w_case, h_case};
        if(is_white_case) {
            SDL_RenderCopy(win->getRender(), w_case_0_, nullptr, &r);
        } else {
            SDL_RenderCopy(win->getRender(), b_case_0_, nullptr, &r);
            //SDL_RenderCopy(win->getRender(), w_piece_[KING], nullptr, &r);
        }
    }
    for(auto piece: game_.getBoard().getPiecesInGame()) {
        int x = piece->getPos_x() * w_case + font_space + board->x;
        int y = (7-piece->getPos_y()) * h_case + board->y;
        SDL_Rect r = {x, y, w_case, h_case};
        if(piece->getColor() == WHITE) {
            SDL_RenderCopy(
                    win->getRender(),
                    win->getWhitePieces()[piece->get_type()],
                    nullptr, &r);
        } else {
            SDL_RenderCopy(
                    win->getRender(),
                    win->getBlackPieces()[piece->get_type()],
                    nullptr, &r);
        }
    }
}


#pragma clang diagnostic pop