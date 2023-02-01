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

        board_(tmp.getTo().first, tmp.getTo().second)->move(tmp.getFrom().first, tmp.getFrom().second);

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

Board &Game::getBoard() {
    return board_;
}

Color Game::getCurrentPlayer() const {
    return current_player_;
}

const vector<Historic> &Game::getMoveHistory() const {
    return move_history_;
}

void Game::addHistory(Historic h) {
    move_history_.push_back(h);
}
