//
// Created by p00ri on 28/01/2023.
//
#pragma once
#include "Piece.h"
#include <utility>

using namespace std;

enum MoveType {NORMAL, L_CAST, R_CAST, PROMOTION};

class Historic {
private:
    Piece* moving_{};
    pair<int,int> from_;
    pair<int,int> to_;
    Piece* destroyed_{};
    MoveType moveType_;
    Piece_Type promote_;

public:
    Historic() = default;
    Historic(Historic const& h) = default;
    Historic& operator=(Historic const& h) = default;

    Historic(Piece* moving, int x1, int y1, int x2, int y2, Piece* destroyed = nullptr, MoveType moveType = NORMAL,
             Piece_Type promote = KING);

    Piece *getMoving() const;
    const pair<int, int> &getFrom() const;
    const pair<int, int> &getTo() const;
    Piece *getDestroyed() const;
    MoveType getMoveType() const;
    Piece_Type getPromote() const;

    void setMoveType(MoveType moveType);

};