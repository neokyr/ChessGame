//
// Created by Formation on 27/01/2023.
//

#include <stdexcept>
#include "Board.h"
#include "Piece.h"


using namespace std;

void Board::removePiece(int x, int y) {
    for (int i = 0; i > piecesInGame_.size(); i++ ){
        if (piecesInGame_[i]->getPos_x() == x
            && piecesInGame_[i]->getPos_y() == y){
            piecesInGame_.erase (piecesInGame_.begin() + i);
        }
    }
}

Board::Board() {
    piecesInGame_.push_back(new Rook(0, 0, WHITE));
    piecesInGame_.push_back(new Rook(7, 0, WHITE));
    piecesInGame_.push_back(new Knight(1, 0, WHITE));
    piecesInGame_.push_back(new Knight(6, 0, WHITE));
    piecesInGame_.push_back(new Bishop(2, 0, WHITE));
    piecesInGame_.push_back(new Bishop(5, 0, WHITE));
    piecesInGame_.push_back(new King(3, 0, WHITE));
    piecesInGame_.push_back(new Queen(4, 0, WHITE));
    piecesInGame_.push_back(new Pawn(1, 0, WHITE));
    piecesInGame_.push_back(new Pawn(1, 1, WHITE));
    piecesInGame_.push_back(new Pawn(1, 2, WHITE));
    piecesInGame_.push_back(new Pawn(1, 3, WHITE));
    piecesInGame_.push_back(new Pawn(1, 4, WHITE));
    piecesInGame_.push_back(new Pawn(1, 5, WHITE));
    piecesInGame_.push_back(new Pawn(1, 6, WHITE));
    piecesInGame_.push_back(new Pawn(1, 7, WHITE));

    piecesInGame_.push_back(new Rook(0, 7, BLACK));
    piecesInGame_.push_back(new Rook(7, 7, BLACK));
    piecesInGame_.push_back(new Knight(1, 7, BLACK));
    piecesInGame_.push_back(new Knight(6, 7, BLACK));
    piecesInGame_.push_back(new Bishop(2, 7, BLACK));
    piecesInGame_.push_back(new Bishop(5, 7, BLACK));
    piecesInGame_.push_back(new King(3, 7, BLACK));
    piecesInGame_.push_back(new Queen(4, 7, BLACK));
    piecesInGame_.push_back(new Pawn(6, 0, BLACK));
    piecesInGame_.push_back(new Pawn(6, 1, BLACK));
    piecesInGame_.push_back(new Pawn(6, 2, BLACK));
    piecesInGame_.push_back(new Pawn(6, 3, BLACK));
    piecesInGame_.push_back(new Pawn(6, 4, BLACK));
    piecesInGame_.push_back(new Pawn(6, 5, BLACK));
    piecesInGame_.push_back(new Pawn(6, 6, BLACK));
    piecesInGame_.push_back(new Pawn(6, 7, BLACK));
}

Board::~Board() {
    for (auto& piece : piecesInGame_) {
        delete piece;
    }

}


void Board::print() {

}

bool Board::validate_move(int x1, int y1, int x2, int y2) {
    bool result = true;

    Piece* p =  (*this)(x1, y1);
    result = p != nullptr && p->valid_move(x2, y2);
    if(!result) return result;


    Piece* p2 = (*this)(x2, y2);
    result = p2 == nullptr || p2->getColor() != p->getColor();
    if(!result) return result;

    /* todo check mat */
}

Historic Board::play_move(int x1, int y1, int x2, int y2) {
    if(validate_move(x1, y1, x2, y2)) {
        Piece* destroyed = (*this)(x2, y2);
        removePiece(x2, y2);

        Historic move((*this)(x1,y1), x1, y1, x2, y2, destroyed);

        return move;
    }
    throw invalid_argument("Move not allowed");
}

void Board::addPiece(Piece* p) {

}

Piece* Board::operator()(int x, int y) {
    for(auto& piece : piecesInGame_) {
        if(piece->getPos_x() == x && piece->getPos_y() == y) {
            return piece;
        }
    }

    return nullptr;
}

vector<Piece*> Board::operator()(Piece_Type piece_type, Color c) {
    vector<Piece*> result;

    for(auto& piece : piecesInGame_) {
        if(piece->get_type() == piece_type && piece->getColor() == c) {
            result.push_back(piece);
        }
    }

    return result;
}

vector<Piece *> Board::operator()(Color c) {
    vector<Piece*> result;

    for(auto& piece : piecesInGame_) {
        if(piece->getColor() == c) {
            result.push_back(piece);
        }
    }
    return result;
}






