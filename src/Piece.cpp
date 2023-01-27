//
// Created by Formation on 27/01/2023.
//

#include "Piece.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Piece::Piece(int x, int y, Color c) : position_x_(x), position_y_(y), c_(c) {
}

void Piece::move(int x, int y) {
    position_x_ = x;
    position_y_ = y;
}


int Piece::getPos_x() const {
    return position_x_;
}

int Piece::getPos_y() const {
    return position_y_;
}

King::King(int x, int y, Color c) : Piece(x, y, c) {
}

bool King::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());
    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return false;
    }

    else if (abs(xm) > 1 || abs(ym) > 1) {
        return false;
    }
    return true;
}

Piece_Type King::get_type() {
    return KING;
}

Queen::Queen(int x, int y, Color c) : Piece(x, y, c) {

}

bool Queen::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return false;
    }

    if ((abs(xm) != abs(ym))
        && (x != getPos_x())
        && (y != getPos_y())){
        return false;
    }

return true;
}

Piece_Type Queen::get_type() {
    return QUEEN;
}

Rook::Rook(int x, int y, Color c) : Piece(x, y, c) {

}

bool Rook::valid_move(int x, int y) {
    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return false;
    }

    if ((x != getPos_x())
        && (y != getPos_y())){
        return false;
    }
    return true;
}

Piece_Type Rook::get_type() {
    return ROOK;
}

Knight::Knight(int x, int y, Color c) : Piece(x, y, c) {

}

bool Knight::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return false;
    }

    if ((abs(xm) == 2 && abs(ym) == 1)
        || (abs(xm) == 1 && abs(ym) == 2)) {
        return true;
    }
    return false;
}

Piece_Type Knight::get_type() {
    return KNIGHT;
}

Bishop::Bishop(int x, int y, Color c) : Piece(x, y, c) {

}

bool Bishop::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return false;
    }

    if (abs(xm) != abs(ym)){
        return false;
    }
    return true;
}

Piece_Type Bishop::get_type() {
    return BISHOP;
}

Pawn::Pawn(int x, int y, Color c) {

}

bool Pawn::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());
    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return false;
    }
    else if ()

        (abs(xm) > 1 || abs(ym) > 1) {
        return false;
    }
    return true;
}


Piece_Type Pawn::get_type() {
    return PAWN;
}

Piece Pawn::upgrade(Piece_Type e) {
  //  return;
}

