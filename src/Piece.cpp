//
// Created by Formation on 27/01/2023.
//

#include "Piece.h"
#include <iostream>

using namespace std;

Piece::Piece(int x, int y, Color c) : position_x_(x), position_y_(y), c_(c){
}

void Piece::move(int x, int y) {
    position_x_ = x;
    position_y_ = y;
    return;
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
    if (x > 7 || x < 0 || y > 7 || y < 0){
        return false;

    }
    else if ( xm > 1 || ym > 1){
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
    return false;
}

Piece_Type Queen::get_type() {
    return QUEEN;
}

Rook::Rook(int x, int y, Color c) : Piece(x, y, c) {

}

bool Rook::valid_move(int x, int y) {
    return false;
}

Piece_Type Rook::get_type() {
    return ROOK;
}

Knight::Knight(int x, int y, Color c) : Piece(x, y, c) {

}

bool Knight::valid_move(int x, int y) {
    return false;
}

Bishop::Bishop(int x, int y, Color c) : Piece(x, y, c) {

}

bool Bishop::valid_move(int x, int y) {
    return false;
}

Pawn::Pawn(int x, int y, bool color) {

}

bool Pawn::valid_move(int x, int y) {
    return false;
}

void Pawn::move(int x, int y) {
    Piece::move(x, y);
}

Piece Pawn::upgrade(Evolved e) {
    return Piece(0, 0, BLACK);
}

