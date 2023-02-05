//
// Created by Formation on 26/01/2023.
//
#pragma once

#include <vector>
#include "Piece.h"
#include "Historic.h"

using namespace std;

class Board {
private:
    vector<Piece*> piecesInGame_;

public:
    Board();
    ~Board();

    void print();
    bool validate_move(int x1, int y1, int x2, int y2);
    Historic play_move(int x1, int y1, int x2, int y2);
    Historic promote(int x, int y, Piece_Type newType);

    void addPiece(Piece* p);
    Piece* removePiece(int x, int y);
    void reInit();

    Piece* operator()(int x, int y) const;
    vector<Piece*> operator()(Piece_Type piece, Color c) const;
    vector<Piece*> operator()(Color c) const;

    bool is_check(Color color) const;

    const vector<Piece *> &getPiecesInGame() const;

    bool is_check_mat(Color color);
    bool is_pat(Color color);
    bool can_castling(Color color);
    bool can_big_castling(Color color);

    bool validate_move_without_check(int x1, int y1, int x2, int y2) const;
};