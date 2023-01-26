//
// Created by Formation on 26/01/2023.
//
#pragma once

class Board {

public:
    Board();
    void print();
    bool validate_move(int x1, int y1, int x2, int y2);
    void play_move(int x1, int y1, int x2, int y2);
};