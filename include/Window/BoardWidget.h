//
// Created by Formation on 27/01/2023.
//
#pragma once

#include "Widget.h"
#include "Game.h"
#include "Window.h"

/*#include "Board.h"
#include "Game.h"*/

class BoardWidget : public Widget {
private:
    Game& game_;
    SDL_Texture *w_case_0_, *w_case_1_, *b_case_0_, *b_case_1_;
    vector<SDL_Texture *> numbers_, letters_, w_piece_, b_piece_;
    int is_moving_x_ = -1;
    int is_moving_y_ = -1;
    int pos_mouse_x_ = 0;
    int pos_mouse_y_ = 0;
    int h_font_ = 30;
    int w_font_ = (int) (h_font_ * 0.8);
    int font_space_ = 40;

    pair<int, int> getCase(int xWin, int yWin);
    void place_piece(Piece *piece, Window *win, int x, int y, int piece_size);
public:
    BoardWidget(int x, int y, int w, Game& game);

    void handleEvent(SDL_Event &e) override;
    void print() override;
};