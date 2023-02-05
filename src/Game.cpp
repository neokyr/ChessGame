#include <stdexcept>
#include "Game.h"

Game::Game() : board_(Board()), current_player_(WHITE), move_history_(vector<Historic>()) {}

void Game::new_game() {
    board_.reInit();
    current_player_ = WHITE;
    deleteMoveHistory();
}

void Game::cancel_move() {
    if(!move_history_.empty()) {
        Historic tmp = move_history_.back();
        move_history_.erase(move_history_.end());

        if(tmp.getMoveType() == PROMOTION && tmp.getTo() == tmp.getFrom()) {
            if(tmp.getDestroyed() == nullptr) throw runtime_error("Corrupted history");
            Piece* p = board_.removePiece(tmp.getTo().first, tmp.getTo().second);
            delete p;
            board_.addPiece(tmp.getDestroyed());
            cancel_move();
        } else {
            if(tmp.getMoveType() == L_CAST) {
                int y = tmp.getMoving()->getColor() == WHITE ? 0: 7;
                getBoard()(3, y)->move(0,y);
            } else if (tmp.getMoveType() == R_CAST) {
                int y = tmp.getMoving()->getColor() == WHITE ? 0: 7;
                getBoard()(5, y)->move(7,y);
            }


            board_(tmp.getTo().first, tmp.getTo().second)->unMove(tmp.getFrom().first, tmp.getFrom().second);
            board_.update_last_move(!move_history_.empty()?move_history_.back():Historic());
            if(tmp.getDestroyed() != nullptr) {
                board_.addPiece(tmp.getDestroyed());
            }
            change_player();
        }

    }
}

void Game::change_player() {
    current_player_ = current_player_ == WHITE ? BLACK : WHITE;
}

bool Game::is_check(Color c) {
    return board_.is_check(c);
}

Board &Game::getBoard() {
    return board_;
}

Color Game::getCurrentPlayer() const {
    return current_player_;
}

const vector<Historic> &Game::getMoveHistory() const {
    return move_history_;
}

bool Game::is_check_mat(Color c) {
    return board_.is_check_mat(c);
}

bool Game::is_pat(Color c) {
    return board_.is_pat(c);
}

bool Game::can_castling(Color c) {
    return board_.can_castling(c);
}

bool Game::can_big_castling(Color c) {
    return board_.can_big_castling(c);
}

void Game::addHistory(Historic h) {
    move_history_.push_back(h);

}

void Game::deleteMoveHistory() {
    for(auto history : move_history_) {
        delete history.getDestroyed();
    }
    move_history_ = vector<Historic>();
}

Game::~Game() {
    deleteMoveHistory();
}
