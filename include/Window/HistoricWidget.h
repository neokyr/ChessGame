//
// Created by p00ri on 29/01/2023.
//
#pragma once
#include "ScrollableWidget.h"
#include "Historic.h"


class HistoricWidget : public ScrollableWidget{
private:
public:
    HistoricWidget(int x, int y, int w, int h, const string &bgPath, int padding);
};