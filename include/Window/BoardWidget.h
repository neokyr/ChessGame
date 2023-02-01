//
// Created by Formation on 27/01/2023.
//
#pragma once

#include "Widget.h"
#include "Game.h"

/*#include "Board.h"
#include "Game.h"*/

class BoardWidget : public Widget {
private:
    Game game_;
    SDL_Texture *w_case_0_, *w_case_1_, *b_case_0_, *b_case_1_;
    vector<SDL_Texture *> numbers_, letters_, w_piece_, b_piece_;


public:
    BoardWidget(int x, int y, int w, Game& game);

    void handleEvent(SDL_Event &e) override;

    void print() override;
};