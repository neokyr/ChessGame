//
// Created by Formation on 26/01/2023.
//
#pragma once

#include <string>
#include "Piece.h"

using namespace std;

class Player {
private:
    Color player_color_;
    string name_;

public:
    Player(string name, Color player_color );
    void play_move(int x1, int y1, int x2, int y2);
    void get_move();
};