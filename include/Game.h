//
// Created by Formation on 26/01/2023.
//
#pragma once

#include "Board.h"
#include "Piece.h"
#include "vector"

using namespace std;

class Game {
private:
    Board board_;
    Color current_player_;
    vector<pair<int, int>> move_history_;

public:
    Game();
    void change_player();
    void cancel_move();
    bool check_mat(Color c, bool check_mat = false);
    bool is_pat(Color c);
    bool can_castling(Color C);
    bool can_big_castling(Color C);
};
