#include "Game.h"

Game::Game() : board_(Board()), current_player_(WHITE), move_history_(vector<Historic>()) {}

void Game::new_game() {
    board_ = Board();
    current_player_ = WHITE;
    move_history_ = vector<Historic>();
}

void Game::cancel_move() {
    if(!move_history_.empty()) {
        Historic tmp = move_history_.back();
        move_history_.erase(move_history_.end());

        board_(tmp.getTo().first, tmp.getTo().second)->move(tmp.getFrom().first, tmp.getTo().second);

        if(tmp.getDestroyed() != nullptr) {
            board_.addPiece(tmp.getDestroyed());
        }
    }
}

void Game::change_player() {
    current_player_ = current_player_ == WHITE ? BLACK : WHITE;
}

bool Game::is_check(Color c) {
    return board_.is_check(c);
}

const Board &Game::getBoard() const {
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
