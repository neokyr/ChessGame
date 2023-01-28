//
// Created by Formation on 27/01/2023.
//

#include "Board.h"
#include "Piece.h"


using namespace std;

void Board::removePiece(int x, int y) {
    for (int i = 0; i > PiecesInGame_.size(); i++ ){
        if (PiecesInGame_[i]->getPos_x() == x
        && PiecesInGame_[i]->getPos_y() == y){
            PiecesInGame_.erase (PiecesInGame_.begin()+i);
        }
    }
}

Board::Board() {

}

void Board::print() {

}

bool Board::validate_move(int x1, int y1, int x2, int y2) {

    return false;
}

void Board::play_move(int x1, int y1, int x2, int y2) {

}

void Board::addPiece(Piece* p) {
    PiecesInGame_.push_back(new Rook(0, 0, WHITE));
    PiecesInGame_.push_back(new Rook(7, 0, WHITE));
    PiecesInGame_.push_back(new Knight(1, 0, WHITE));
    PiecesInGame_.push_back(new Knight(6, 0, WHITE));
    PiecesInGame_.push_back(new Bishop(2, 0, WHITE));
    PiecesInGame_.push_back(new Bishop(5, 0, WHITE));
    PiecesInGame_.push_back(new King(3, 0, WHITE));
    PiecesInGame_.push_back(new Queen(4, 0, WHITE));
    PiecesInGame_.push_back(new Pawn(1, 0, WHITE));
    PiecesInGame_.push_back(new Pawn(1, 1, WHITE));
    PiecesInGame_.push_back(new Pawn(1, 2, WHITE));
    PiecesInGame_.push_back(new Pawn(1, 3, WHITE));
    PiecesInGame_.push_back(new Pawn(1, 4, WHITE));
    PiecesInGame_.push_back(new Pawn(1, 5, WHITE));
    PiecesInGame_.push_back(new Pawn(1, 6, WHITE));
    PiecesInGame_.push_back(new Pawn(1, 7, WHITE));

    PiecesInGame_.push_back(new Rook(0, 7, BLACK));
    PiecesInGame_.push_back(new Rook(7, 7, BLACK));
    PiecesInGame_.push_back(new Knight(1, 7, BLACK));
    PiecesInGame_.push_back(new Knight(6, 7, BLACK));
    PiecesInGame_.push_back(new Bishop(2, 7, BLACK));
    PiecesInGame_.push_back(new Bishop(5, 7, BLACK));
    PiecesInGame_.push_back(new King(3, 7, BLACK));
    PiecesInGame_.push_back(new Queen(4, 7, BLACK));
    PiecesInGame_.push_back(new Pawn(6, 0, BLACK));
    PiecesInGame_.push_back(new Pawn(6, 1, BLACK));
    PiecesInGame_.push_back(new Pawn(6, 2, BLACK));
    PiecesInGame_.push_back(new Pawn(6, 3, BLACK));
    PiecesInGame_.push_back(new Pawn(6, 4, BLACK));
    PiecesInGame_.push_back(new Pawn(6, 5, BLACK));
    PiecesInGame_.push_back(new Pawn(6, 6, BLACK));
    PiecesInGame_.push_back(new Pawn(6, 7, BLACK));
}




