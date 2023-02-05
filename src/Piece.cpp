//
// Created by Formation on 27/01/2023.
//

#include "Piece.h"
#include <iostream>

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

void Piece::unMove(int x, int y) {
    position_x_ = x;
    position_y_ = y;
}

King::King(int x, int y, Color c) : Piece(x, y, c), nb_moves_(0) {
}

Movement King::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());
    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return {false};
    }

    if(nb_moves_ == 0 && ym == 0 && abs(xm) == 2) {
        return {true};
    }

    if (abs(xm) > 1 || abs(ym) > 1) {
        return {false};
    }

    return {true};
}

Piece_Type King::get_type() {
    return KING;
}

void King::move(int x, int y) {
    Piece::move(x, y);
    nb_moves_ += 1;
}

void King::unMove(int x, int y) {
    if(nb_moves_ == 0) throw runtime_error("UnMove shouldn't be called");
    Piece::unMove(x, y);
    nb_moves_ -= 1;
}

Queen::Queen(int x, int y, Color c) : Piece(x, y, c) {}

Movement Queen::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return {false};
    }

    if ((abs(xm) != abs(ym))
        && (x != getPos_x())
        && (y != getPos_y())){
        return {false};
    }

return {true};
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
        return {false};
    }


    if ((x != getPos_x())
        && (y != getPos_y())){
        return {false};
    }
    return {true};
}

Piece_Type Rook::get_type() {
    return ROOK;
}

void Rook::move(int x, int y) {
    Piece::move(x, y);
    nb_move++;
}

void Rook::unMove(int x, int y) {
    if(nb_move == 0) throw runtime_error("UnMove shouldn't be called");
    Piece::unMove(x, y);
    nb_move -= 1;
}

Knight::Knight(int x, int y, Color c) : Piece(x, y, c) {

}

Movement Knight::valid_move(int x, int y) {
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if (x > 7 || x < 0 || y > 7 || y < 0) {
        return {false};
    }

    if ((abs(xm) == 2 && abs(ym) == 1)
        || (abs(xm) == 1 && abs(ym) == 2)) {
        return {true, true};
    }
    return {false};
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
        return {false};
    }

    if (abs(xm) != abs(ym)){
        return {false};
    }
    return {true};
}

Piece_Type Bishop::get_type() {
    return BISHOP;
}

Pawn::Pawn(int x, int y, Color c) : Piece(x,y,c) {}

Movement Pawn::valid_move(int x, int y) {
    if(x <0 || x> 7 || y <0 || y > 7) return {false};
    int xm = (x - getPos_x());
    int ym = (y - getPos_y());

    if(getColor() == WHITE) {
        if(ym > 2 || ym < 1 || (getPos_y() != 1 && ym != 1)) return {false};
        if(abs(xm) == 1 && ym == 1) return {true, false,true,true};
        if(xm == 0) return {true, false, false};
    } else {
        if(ym < -2 || ym > -1 || (getPos_y() != 6 && ym != -1)) return {false};
        if(abs(xm) == 1 && ym == -1) return {true, false,true,true};
        if(xm == 0) return {true, false, false};
    }


    /*if ((getColor() == WHITE && getPos_y() == 1) || (getColor() == BLACK && getPos_y() == 6)) {
        if (abs(ym) <= 0 || abs(ym) > 2 || abs(ym) == 2 && abs(xm) != 0 || abs(xm) > 1) {
            return Movement(false);
        }
        else if (getColor() == WHITE && abs(xm) == 1 && ym == 1){
                    return Movement(true, true, true, true);
                }
        else if (getColor() == BLACK && abs(xm) == 1 && ym == -1){
            return Movement(true, true, true, true);
        }
    }*/
    return {false};
}


Piece_Type Pawn::get_type() {
    return PAWN;
}

Piece& Pawn::upgrade(Piece_Type e) {
    return *this;
}

