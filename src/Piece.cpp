//
// Created by Formation on 27/01/2023.
//

#include "Piece.h"
#include <iostream>
#include <stdlib.h>

using namespace std;


bool Movement::isDirect() const {
    return isDirect_;
}

bool Movement::isCanEat() const {
    return canEat_;
}

bool Movement::isValid() const {
    return isValid_;
}

bool Movement::isEatOnly() const {
    return eatOnly_;
}

Movement::Movement(bool isValid, bool isDirect=false, bool canEat=true, bool eatOnly=false ) : isValid_(isValid), isDirect_(isDirect), canEat_(canEat),
                                                                             eatOnly_(eatOnly)  {

}


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

Color Piece::getColor() const {
    return c_;
}

King::King(int x, int y, Color c) : Piece(x, y, c) {
}

Movement King::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());
    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return Movement(false);
    }

    else if (abs(xm) > 1 || abs(ym) > 1) {
        return Movement(false);
    }
    else if (abs(xm) == 2){
        return Movement(true);
    }
    return Movement(true);
}

Piece_Type King::get_type() {
    return KING;
}

Queen::Queen(int x, int y, Color c) : Piece(x, y, c) {

}

Movement Queen::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return Movement(false);
    }

    if ((abs(xm) != abs(ym))
        && (x != getPos_x())
        && (y != getPos_y())){
        return Movement(false);
    }

return Movement(true);
}

Piece_Type Queen::get_type() {
    return QUEEN;
}

Rook::Rook(int x, int y, Color c) : Piece(x, y, c) {

}

Movement Rook::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return Movement(false);
    }

    if (already_move_ && getPos_x() == 0) {
        if (xm == 3) {
            return Movement(true, true, false);
        }
        else {
            return Movement(false);
        }
    }
    else if (already_move_ && getPos_x() == 7){
            if (xm == -2){
                return Movement(true, true, false);
            }
            else {
                return Movement(false);
            }
    }

    if ((x != getPos_x())
        && (y != getPos_y())){
        return Movement(false);
    }
    return Movement(true);
}

Piece_Type Rook::get_type() {
    return ROOK;
}

Knight::Knight(int x, int y, Color c) : Piece(x, y, c) {

}

Movement Knight::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return Movement(false);
    }

    if ((abs(xm) == 2 && abs(ym) == 1)
        || (abs(xm) == 1 && abs(ym) == 2)) {
        return Movement(true, true);
    }
    return Movement(false);
}

Piece_Type Knight::get_type() {
    return KNIGHT;
}

Bishop::Bishop(int x, int y, Color c) : Piece(x, y, c) {

}

Movement Bishop::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return Movement(false);
    }

    if (abs(xm) != abs(ym)){
        return Movement(false);
    }
    return Movement(true);
}

Piece_Type Bishop::get_type() {
    return BISHOP;
}

Pawn::Pawn(int x, int y, Color c) : Piece(x,y,c) {}

Movement Pawn::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if ((getColor() == WHITE && getPos_y() == 1) || (getColor() == BLACK && getPos_y() == 6)) {
        if (abs(ym) <= 0 || abs(ym) > 2 || abs(ym) == 2 && abs(xm) != 0 || abs(xm) > 1) {
            return Movement(false);
        }
        else if (getColor() == WHITE && abs(xm) == 1 && ym == 1){
                    return Movement(true, true, true, true);
                }
        else if (getColor() == BLACK && abs(xm) == 1 && ym == -1){
            return Movement(true, true, true, true);
        }
    }
    return Movement(true, false, false);
}


Piece_Type Pawn::get_type() {
    return PAWN;
}

Piece& Pawn::upgrade(Piece_Type e) {
    return *this;
}
