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
    Color current_player;
    vector<pair<int, int>> move_history;

};
