
#include "Window/BoardWidget.h"
#include "Window/Window.h"
#include "Piece.h"


BoardWidget::BoardWidget(int x, int y, int w, Game &game) :
        Widget(x, y, w, w), game_(game) {
    Window *win = Window::getMainWindow();
    EventHandler *handler = EventHandler::getEventHandler();

    handler->subscribe(this);

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
    if (e.type == SDL_MOUSEBUTTONDOWN && is_inside(e.button.x, e.button.y)) {
        pair<int, int> moving = getCase(e.button.x, e.button.y);
        Piece* p = game_.getBoard()(moving.first, moving.second);
        if(p != nullptr && p->getColor() == game_.getCurrentPlayer()) {
            is_moving_x_ = moving.first;
            is_moving_y_ = moving.second;
        }

    } else if (e.type == SDL_MOUSEBUTTONUP ) {
        pair<int, int> pos = getCase(e.button.x, e.button.y);
        if(is_moving_x_ != -1 && pos.first != -1) {
            try {
                Historic r = game_.getBoard().play_move(
                        is_moving_x_,
                        is_moving_y_,
                        pos.first,
                        pos.second);
                game_.addHistory(r);

                game_.change_player();
            } catch (exception& e) {

            }

        }
        is_moving_x_ = -1;
        is_moving_y_ = -1;
    } else if (e.type == SDL_MOUSEMOTION) {
        pos_mouse_x_ = e.motion.x;
        pos_mouse_y_ = e.motion.y;
    }
}

void BoardWidget::print() {
    Window *win = Window::getMainWindow();
    SDL_Rect *board = getPosition();


    int case_size = (board->w - font_space_) / 8;

    for (int i = 7; i >= 0; i--) {
        int x = board->x + (font_space_ - w_font_) / 2;
        int y = board->y + (7 - i) * case_size + (case_size - h_font_) / 2;
        SDL_Rect r = {x, y, w_font_, h_font_};
        SDL_RenderCopy(win->getRender(), letters_[i], nullptr, &r);
    }

    for (int i = 0; i < 8; i++) {
        int x = board->x + i * case_size + font_space_ + (case_size - w_font_) / 2;
        int y = board->y + board->h - font_space_ + (font_space_ - h_font_) / 2;
        SDL_Rect r = {x, y, w_font_, h_font_};
        SDL_RenderCopy(win->getRender(), numbers_[i], nullptr, &r);
    }

    for (int i = 0; i < 64; ++i) {
        bool is_white_case = (i % 2 + i / 8) % 2;
        int x = (i % 8) * case_size + font_space_ + board->x;
        int y = (i / 8) * case_size + board->y;
        SDL_Rect r = {x, y, case_size, case_size};
        if (game_.getBoard().validate_move(is_moving_x_, is_moving_y_, i%8, 7 - i/8)) {
            if(is_white_case) {
                SDL_RenderCopy(win->getRender(), w_case_1_, nullptr, &r);
            } else {
                SDL_RenderCopy(win->getRender(), b_case_1_, nullptr, &r);
            }
        } else {
            if(is_white_case) {
                SDL_RenderCopy(win->getRender(), w_case_0_, nullptr, &r);
            } else {
                SDL_RenderCopy(win->getRender(), b_case_0_, nullptr, &r);
            }
        }
    }
    Piece* selected = game_.getBoard()(is_moving_x_, is_moving_y_);

    int piece_size = case_size - 10;
    for (auto piece: game_.getBoard().getPiecesInGame()) {
        if(selected != nullptr && selected->getPos_x() == piece->getPos_x() && selected->getPos_y() == piece->getPos_y()) {
            continue;
        }
        int x = piece->getPos_x() * case_size + font_space_ + board->x + 5;
        int y = (7 - piece->getPos_y()) * case_size + board->y + 5;

        place_piece(piece, win, x, y, piece_size);
    }
    if(selected != nullptr) {
        place_piece(selected, win, pos_mouse_x_ - piece_size / 2,
                    pos_mouse_y_ - piece_size / 2,
                    piece_size);
    }

}

pair<int, int> BoardWidget::getCase(int xWin, int yWin) {
    int xBoard = getPosition()->x;
    int yBoard = getPosition()->y;
    int size = getPosition()->w;
    int case_size = (size - font_space_) / 8;


    pair<int, int> result(-1, -1);

    if (is_inside(xWin, yWin)) {
        if ((xWin - xBoard) > font_space_ && yWin < (size + yBoard - font_space_)) {
            result.first = (xWin - font_space_ - xBoard) / case_size;
            result.second = 7 - (yWin - yBoard) / case_size;
        }
    }

    return result;
}

void BoardWidget::place_piece(Piece *piece, Window *win, int x, int y, int piece_size) {
    SDL_Rect* board = getPosition();
    int case_size = (board->w - font_space_) / 8;

    SDL_Rect r = {x, y, piece_size, piece_size};

    if (piece->getColor() == WHITE) {
        SDL_RenderCopy(
                win->getRender(),
                w_piece_[piece->get_type()],
                nullptr, &r);
    } else {
        SDL_RenderCopy(
                win->getRender(),
                b_piece_[piece->get_type()],
                nullptr, &r);
    }
}
