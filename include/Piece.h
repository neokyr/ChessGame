//
// Created by Formation on 26/01/2023.
//
#pragma once

enum Color { WHITE, BLACK};


class Piece {
private:
    Color c_;
    int position_x_;
    int position_y_;
public:
    Piece(int x, int y, Color c);
    virtual bool valid_move(int x, int y) =0;
    virtual void move(int x, int y);
};

class King : public Piece {
public:
    King(int x, int y, Color c);
    bool valid_move(int x, int y);
};

class Queen : public Piece {
public:
    Queen(int x, int y, Color c);
    bool valid_move(int x, int y);
};

class Tower : public Piece {
public:
    Tower(int x, int y, Color c);
    bool valid_move(int x, int y);
};

class Knight : public Piece {
public:
    Knight(int x, int y, Color c);
    bool valid_move(int x, int y);
};

class Bishop : public Piece {
public:
    Bishop(int x, int y, Color c);
    bool valid_move(int x, int y);
};

enum Evolved{QUEEN, TOWER, BISHOP, KNIGHT};

class Pawn : public Piece {
private:
    bool already_move_ = false;
public:
    Pawn(int x, int y, bool color);
    bool valid_move(int x, int y);
    void move(int x, int y) override;
    Piece upgrade(Evolved e);

};
