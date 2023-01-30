//
// Created by Formation on 26/01/2023.
//
#pragma once

#include <vector>
#include "Game.h"
#include "Piece.h"
#include "Historic.h"

using namespace std;

class Board {
private:
    vector<Piece*> piecesInGame_;
    Game mainGame_;

    void removePiece(int x, int y);


public:
    Board(Game& game);
    void print();
    bool validate_move(int x1, int y1, int x2, int y2);
    Historic play_move(int x1, int y1, int x2, int y2);

    void addPiece(Piece* p);

    Piece* operator()(int x, int y);
    vector<Piece*> operator()(Piece_Type piece, Color c);
    vector<Piece*> operator()(Color c);
};