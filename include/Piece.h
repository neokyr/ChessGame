//
// Created by Formation on 26/01/2023.
//
#pragma once

enum Color { WHITE, BLACK};


class Piece {
private:
    Color c_;
    int position_x;
    int position_y;
public:
    Piece(int x, int y, Color c);
    virtual bool valid_move(int x, int y) =0;
    virtual void move(int x, int y) = 0;
};

