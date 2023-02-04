//
// Created by p00ri on 29/01/2023.
//
#pragma once
#include "ScrollableWidget.h"
#include "Historic.h"
#include "Game.h"


class HistoricWidget : public ScrollableWidget{
private:
    Game& game_;
public:
    HistoricWidget(int x, int y, int w, int h, const string &bgPath, int padding, Game& game);
    void print() override;
};