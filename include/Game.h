#pragma once

#include "Board.h"
#include "Piece.h"
#include "vector"
#include "Historic.h"

using namespace std;

class Game {
private:
    Board board_;
    Color current_player_;
    vector<Historic> move_history_;

public:
    Game();

    void new_game();
    void cancel_move();
    void change_player();
    bool is_check(Color c);
    bool is_check_mat(Color c);
    bool is_pat(Color c);
    bool can_castling(Color C);
    bool can_big_castling(Color C);

    Board &getBoard();
    Color getCurrentPlayer() const;
    const vector<Historic> &getMoveHistory() const;
    void addHistory(Historic h);
};
