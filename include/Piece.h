//
// Created by Formation on 26/01/2023.
//
#pragma once

enum Color { WHITE, BLACK};
enum Piece_Type{KING, QUEEN, TOWER, BISHOP, KNIGHT, PAWN};

class Piece {
private:
    Color c_;
    int position_x_;
    int position_y_;
public:
    Piece(int x, int y, Color c);
    virtual bool valid_move(int x, int y) = 0;
    virtual void move(int x, int y);
    virtual Piece_Type get_type() = 0;

    int getPos_x() const;
    int getPos_y() const;
};

class King : public Piece {
public:
    King(int x, int y, Color c);
    bool valid_move(int x, int y);

    Piece_Type get_type() override;

};

class Queen : public Piece {
public:
    Queen(int x, int y, Color c);
    bool valid_move(int x, int y);

    Piece_Type get_type() override;
};

class Rook : public Piece {
public:
    Rook(int x, int y, Color c);
    bool valid_move(int x, int y) override;

    Piece_Type get_type() override;

};

class Knight : public Piece {
public:
    Knight(int x, int y, Color c);
    bool valid_move(int x, int y) override;
};

class Bishop : public Piece {
public:
    Bishop(int x, int y, Color c);
    bool valid_move(int x, int y) override;
};

class Pawn : public Piece {
private:
    bool already_move_ = false;
public:
    Pawn(int x, int y, bool color);
    bool valid_move(int x, int y) override;
    void move(int x, int y) override;
    Piece upgrade(Evolved e);

};
