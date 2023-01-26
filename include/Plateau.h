//
// Created by Formation on 26/01/2023.
//
#pragma once

class Plateau {

public:
    Plateau();
    void afficher();
    bool valider_coup(int x1, int y1, int x2, int y2);
    void jouer_coup(int x1, int y1, int x2, int y2);
};