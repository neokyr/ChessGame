//
// Created by Formation on 26/01/2023.
//
#pragma once
#include <vector>

using namespace std;

enum Color { WHITE, BLACK};
enum Piece_Type{KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN};

class Movement{

private:
    bool isDirect_, canEat_, eatOnly_, isValid_;

public:

    Movement(bool isDirect, bool canEat, bool eatOnly, bool isValid);

    bool isDirect() const;
    bool isCanEat() const;
    bool isValid() const;
    bool isEatOnly() const;

};

class Piece {
private:
    Color c_;
    int position_x_;
    int position_y_;

public:
    Piece(int x, int y, Color c);
    virtual Movement valid_move(int x, int y) = 0;
    virtual void move(int x, int y);
    virtual Piece_Type get_type() = 0;
    Color getColor() const;

    int getPos_x() const;
    int getPos_y() const;
};

class King : public Piece {
private:
    bool already_move_ = false;
public:
    King(int x, int y, Color c);
    Movement valid_move(int x, int y);
    void move(int x, int y);

    Piece_Type get_type() override;

};

class Queen : public Piece {
public:
    Queen(int x, int y, Color c);
    Movement valid_move(int x, int y);

    Piece_Type get_type() override;
};

class Rook : public Piece {
private:
    bool already_move_ = false;
public:
    Rook(int x, int y, Color c);
    Movement valid_move(int x, int y) override;

    Piece_Type get_type() override;

};

class Knight : public Piece {
public:
    Knight(int x, int y, Color c);
    Movement valid_move(int x, int y) override;

    Piece_Type get_type() override;

};

class Bishop : public Piece {
public:
    Bishop(int x, int y, Color c);
    Movement valid_move(int x, int y) override;

    Piece_Type get_type() override;

};

class Pawn : public Piece {
private:
    bool already_move_ = false;
public:
    Pawn(int x, int y, Color c);
    Movement valid_move(int x, int y) override;
    void move(int x, int y);
    Piece_Type get_type() override;

    Piece& upgrade(Piece_Type e);

};
