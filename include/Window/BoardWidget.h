//
// Created by Formation on 27/01/2023.
//
#pragma once

#include "Widget.h"
/*#include "Board.h"
#include "Game.h"*/

class BoardWidget : public Widget {
private:
    /*Board board_;
    Game game_;*/
    SDL_Texture *w_case_0_, *w_case_1_, *b_case_0_, *b_case_1_;
    SDL_Texture *w_bishop_, *w_king_, *w_knight_, *w_pawn_, *w_queen_, *w_rook_;
    SDL_Texture *b_bishop_, *b_king_, *b_knight_, *b_pawn_, *b_queen_, *b_rook_;
    vector<SDL_Texture *> numbers_, letters;


public:
    BoardWidget(int x, int y, int w/*, Board& board, Game& game*/);

    void handleEvent(SDL_Event &e) override;

    void print() override;


};