//
// Created by Formation on 26/01/2023.
//
#pragma once

enum color { WHITE, BLACK};


class Piece {
private:
    color c_;
    int position_x;
    int position_y;
public:
    Piece(int x, int y, color c);
    virtual bool deplacement_valide(int x, int y) =0;
    virtual void deplacer(int x, int y) = 0;
};

