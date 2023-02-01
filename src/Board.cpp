//
// Created by Formation on 27/01/2023.
//

#include <stdexcept>
#include "Board.h"
#include "Piece.h"


class Movement;

using namespace std;

Piece* Board::removePiece(int x, int y) {
    for (int i = 0; i < piecesInGame_.size() ; i++ ){
        if (piecesInGame_[i]->getPos_x() == x
            && piecesInGame_[i]->getPos_y() == y){
            Piece* piece = piecesInGame_[i];
            piecesInGame_.erase (piecesInGame_.begin() + i);
            return piece;
        }
    }
    return nullptr;
}

Board::Board(){

    piecesInGame_.push_back(new Rook(0, 0, WHITE));
    piecesInGame_.push_back(new Rook(7, 0, WHITE));
    piecesInGame_.push_back(new Knight(1, 0, WHITE));
    piecesInGame_.push_back(new Knight(6, 0, WHITE));
    piecesInGame_.push_back(new Bishop(2, 0, WHITE));
    piecesInGame_.push_back(new Bishop(5, 0, WHITE));
    piecesInGame_.push_back(new King(3, 0, WHITE));
    piecesInGame_.push_back(new Queen(4, 0, WHITE));
    piecesInGame_.push_back(new Pawn(0, 1, WHITE));
    piecesInGame_.push_back(new Pawn(1, 1, WHITE));
    piecesInGame_.push_back(new Pawn(2, 1, WHITE));
    piecesInGame_.push_back(new Pawn(3, 1, WHITE));
    piecesInGame_.push_back(new Pawn(4, 1, WHITE));
    piecesInGame_.push_back(new Pawn(5, 1, WHITE));
    piecesInGame_.push_back(new Pawn(6, 1, WHITE));
    piecesInGame_.push_back(new Pawn(7, 1, WHITE));

    piecesInGame_.push_back(new Rook(0, 7, BLACK));
    piecesInGame_.push_back(new Rook(7, 7, BLACK));
    piecesInGame_.push_back(new Knight(1, 7, BLACK));
    piecesInGame_.push_back(new Knight(6, 7, BLACK));
    piecesInGame_.push_back(new Bishop(2, 7, BLACK));
    piecesInGame_.push_back(new Bishop(5, 7, BLACK));
    piecesInGame_.push_back(new King(3, 7, BLACK));
    piecesInGame_.push_back(new Queen(4, 7, BLACK));
    piecesInGame_.push_back(new Pawn(0, 6, BLACK));
    piecesInGame_.push_back(new Pawn(1, 6, BLACK));
    piecesInGame_.push_back(new Pawn(2, 6, BLACK));
    piecesInGame_.push_back(new Pawn(3, 6, BLACK));
    piecesInGame_.push_back(new Pawn(4, 6, BLACK));
    piecesInGame_.push_back(new Pawn(5, 6, BLACK));
    piecesInGame_.push_back(new Pawn(6, 6, BLACK));
    piecesInGame_.push_back(new Pawn(7, 6, BLACK));
}

Board::~Board() {
    for (auto& piece : piecesInGame_) {
        //delete piece;
        /* TODO resolve nullPtr exception on destroy */
    }

}


void Board::print() {

}

bool Board::validate_move(int x1, int y1, int x2, int y2) {
    Piece* p =  (*this)(x1, y1);
    if(p == nullptr) return false;

    Movement m = p->valid_move(x2, y2);
    if(!m.isValid()) return false;

    if(!m.isDirect()) {
        int dX = x2-x1;
        int dY = y2-y1;
        int biggest = max(abs(dX), abs(dY));
        for(int i = 1; i < biggest ; i++) {
            int nX = x1 + i * dX /biggest;
            int nY = y1 + i * dY /biggest;
            if((*this)(nX, nY) != nullptr) return false;
        }
    }

    Piece* p2 = (*this)(x2, y2);
    if(p2 == nullptr && m.isEatOnly()) return false;
    if(p2 != nullptr && p2->getColor() == p->getColor()) return false;
    if(p2 != nullptr && !m.isCanEat()) return false;


    return true;
    /* todo check is_mat */
}

Historic Board::play_move(int x1, int y1, int x2, int y2) {
    if(validate_move(x1, y1, x2, y2)) {
        Piece* p = (*this)(x1,y1);
        Piece* destroyed = removePiece(x2, y2);

        Historic move(p, x1, y1, x2, y2, destroyed);
        p->move(x2,y2);
        return move;
    }
    throw invalid_argument("Move not allowed");
}

void Board::addPiece(Piece* p) {
    piecesInGame_.push_back(p);
}

Piece* Board::operator()(int x, int y) const{
    for(auto& piece : piecesInGame_) {
        if(piece->getPos_x() == x && piece->getPos_y() == y) {
            return piece;
        }
    }

    return nullptr;
}

vector<Piece*> Board::operator()(Piece_Type piece_type, Color c) const{
    vector<Piece*> result;

    for(auto& piece : piecesInGame_) {
        if(piece->get_type() == piece_type && piece->getColor() == c) {
            result.push_back(piece);
        }
    }

    return result;
}

vector<Piece *> Board::operator()(Color c) const{
    vector<Piece*> result;

    for(auto& piece : piecesInGame_) {
        if(piece->getColor() == c) {
            result.push_back(piece);
        }
    }
    return result;
}

bool Board::is_check(Color color) {
    bool result = false;
    Color other = color == WHITE ? BLACK: WHITE;
    vector<Piece*> pieces = (*this)(other);
    Piece *king = (*this)(KING, color).at(0);
    int x = king->getPos_x(), y = king->getPos_y();

    for(auto piece : pieces) {
        result = result || validate_move(piece->getPos_x(), piece->getPos_y(), x, y);
    }

    return result;
}

const vector<Piece *> &Board::getPiecesInGame() const {
    return piecesInGame_;
}






