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
            && piecesInGame_[i]->getPos_y() == y) {
            Piece *piece = piecesInGame_[i];
            piecesInGame_.erase(piecesInGame_.begin() + i);
            return piece;
        }
    }
    return nullptr;
}

Board::Board() {
    reInit();
}

Board::~Board() {
    for (auto &piece: piecesInGame_) {
        delete piece;
    }

}

void Board::print() {

}

bool Board::validate_move(int x1, int y1, int x2, int y2) {
    bool res = validate_move_without_check(x1, y1, x2, y2);
    if(!res) return false;
    Piece *p = (*this)(x1, y1);
    Piece *p2 = (*this)(x2, y2);


    if (p2 != nullptr) p2 = removePiece(x2, y2);
    p->move(x2, y2);
    res = !is_check(p->getColor());
    p->unMove(x1, y1);
    if (p2 != nullptr) addPiece(p2);


    return res;
}
bool Board::validate_move_without_check(int x1, int y1, int x2, int y2) const {

    Piece *p = (*this)(x1, y1);
    if (p == nullptr) return false;


    Movement m = p->valid_move(x2, y2);
    if (!m.isValid()) return false;


    if (!m.isDirect()) {
        int dX = x2 - x1;
        int dY = y2 - y1;
        int biggest = max(abs(dX), abs(dY));
        for (int i = 1; i < biggest; i++) {
            int nX = x1 + i * dX / biggest;
            int nY = y1 + i * dY / biggest;
            if ((*this)(nX, nY) != nullptr) return false;
        }
    }

    Piece *p2 = (*this)(x2, y2);
    if (p2 == nullptr && m.isEatOnly()) return false;
    if (p2 != nullptr && p2->getColor() == p->getColor()) return false;
    if (p2 != nullptr && !m.isCanEat()) return false;

    return true;
}

Historic Board::play_move(int x1, int y1, int x2, int y2) {

    if (validate_move(x1, y1, x2, y2)) {
        Piece *p = (*this)(x1, y1);
        Piece *destroyed = removePiece(x2, y2);

        Historic move(p, x1, y1, x2, y2, destroyed);
        p->move(x2, y2);

        if(p->get_type() == PAWN && (y2 == 0 || y2 == 7)) {
            move.setMoveType(PROMOTION);
        }

        return move;
    }
    throw invalid_argument("Move not allowed");
}

void Board::addPiece(Piece *p) {
    piecesInGame_.push_back(p);
}

Piece *Board::operator()(int x, int y) const {
    for (auto &piece: piecesInGame_) {
        if (piece->getPos_x() == x && piece->getPos_y() == y) {
            return piece;
        }
    }

    return nullptr;
}
vector<Piece *> Board::operator()(Piece_Type piece_type, Color c) const {
    vector<Piece *> result;

    for (auto &piece: piecesInGame_) {
        if (piece->get_type() == piece_type && piece->getColor() == c) {
            result.push_back(piece);
        }
    }

    return result;
}
vector<Piece *> Board::operator()(Color c) const {
    vector<Piece *> result;

    for (auto &piece: piecesInGame_) {
        if (piece->getColor() == c) {
            result.push_back(piece);
        }
    }
    return result;
}
const vector<Piece *> &Board::getPiecesInGame() const {
    return piecesInGame_;
}

bool Board::is_check(Color color) const {
    bool result = false;
    Color other = color == WHITE ? BLACK : WHITE;
    vector<Piece *> pieces = (*this)(other);
    Piece *king;
    try {
        king = (*this)(KING, color).at(0);
    } catch (exception &e) {
        return false;
    }
    int x = king->getPos_x(), y = king->getPos_y();

    for (auto piece: pieces) {
        result = result || validate_move_without_check(piece->getPos_x(), piece->getPos_y(), x, y);
    }

    return result;
}
bool Board::is_check_mat(Color color) {
    if(!is_check(color)) return false;
    vector<Piece*> cPieces = (*this)(color);

    bool result = false;
    for(auto piece : cPieces) {
        for (int i = 0; i < 64 && !result; ++i) {
            result = validate_move(piece->getPos_x(), piece->getPos_y(), i%8, i/8);
        }
        if(result) break;
    }

    return !result;
}
bool Board::is_pat(Color color) {
    if(!is_check(color)) {
        bool result = false;
        vector<Piece*> cPieces = (*this)(color);

        for(auto piece : cPieces) {
            for (int i = 0; i < 64 && !result; ++i) {
                result = validate_move(piece->getPos_x(), piece->getPos_y(), i%8, i/8);
            }
            if(result) break;
        }
        return !result;
    }
    return false;
}
bool Board::can_castling(Color color) {
    Piece *k;
    Piece *r;
    if (color == WHITE) {
        r = (*this)(7, 0);
        k = (*this)(4, 0);
    } else {
        r = (*this)(7, 7);
        k = (*this)(4, 7);
    }
    if (r == nullptr || r->get_type() != ROOK || r->getColor() != color) {
        return false;
    }
    if (is_check(color) || k == nullptr || k->get_type() != KING || k->getColor() != color) {
        return false;
    }
    Movement m = r->valid_move(5, color == WHITE ? 0 : 7);
    if (!m.isValid() || !m.isDirect()) {
        return false;
    }
    if (validate_move(k->getPos_x(), k->getPos_y(), k->getPos_x() + 2, k->getPos_y())) {
        return true;
    }
    return false;
}
bool Board::can_big_castling(Color color) {
    Piece *k;
    Piece *r;
    if (color == WHITE) {
        r = (*this)(0, 0);
        k = (*this)(4, 0);
    } else {
        r = (*this)(0, 7);
        k = (*this)(4, 7);
    }
    if (r == nullptr || r->get_type() != ROOK || r->getColor() != color) {
        return false;
    }
    if (is_check(color) || k == nullptr || r->get_type() != KING || r->getColor() != color) {
        return false;
    }
    Movement m = r->valid_move(3, color == WHITE ? 0 : 7);
    if (!m.isValid() || !m.isDirect()) {
        return false;
    }
    if (validate_move(k->getPos_x(), k->getPos_y(), k->getPos_x() - 2, k->getPos_y())) {
        return true;
    }
    return false;
}

Historic Board::promote(int x, int y, Piece_Type newType) {
    Piece* p = (*this)(x,y);

    if(p == nullptr || p->get_type() != PAWN) {
        throw invalid_argument("No pawn in " + to_string(x) + " " + to_string(y));
    }
    Piece* newPiece;
    switch (newType) {
        case BISHOP: newPiece = new Bishop(x, y,p->getColor());
            break;
        case KNIGHT: newPiece = new Knight(x, y,p->getColor());
            break;
        case QUEEN: newPiece = new Queen(x, y,p->getColor());
            break;
        case ROOK: newPiece = new Rook(x, y,p->getColor());
            break;
        default:
            throw invalid_argument("Invalid type : " + to_string(newType));
    }

    p = removePiece(x,y);
    if(p == nullptr) throw runtime_error("Error deleting pawn");
    addPiece(newPiece);


    return {newPiece, x, y, x, y, p, PROMOTION};
}

void Board::reInit() {
    for(auto& piece: piecesInGame_) {
        delete piece;
    }
    piecesInGame_ = vector<Piece*>();

    piecesInGame_.push_back(new Rook(0, 0, WHITE));
    piecesInGame_.push_back(new Rook(7, 0, WHITE));
    piecesInGame_.push_back(new Knight(1, 0, WHITE));
    piecesInGame_.push_back(new Knight(6, 0, WHITE));
    piecesInGame_.push_back(new Bishop(2, 0, WHITE));
    piecesInGame_.push_back(new Bishop(5, 0, WHITE));
    piecesInGame_.push_back(new Queen(3, 0, WHITE));
    piecesInGame_.push_back(new King(4, 0, WHITE));
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
    piecesInGame_.push_back(new Queen(3, 7, BLACK));
    piecesInGame_.push_back(new King(4, 7, BLACK));
    piecesInGame_.push_back(new Pawn(0, 6, BLACK));
    piecesInGame_.push_back(new Pawn(1, 6, BLACK));
    piecesInGame_.push_back(new Pawn(2, 6, BLACK));
    piecesInGame_.push_back(new Pawn(3, 6, BLACK));
    piecesInGame_.push_back(new Pawn(4, 6, BLACK));
    piecesInGame_.push_back(new Pawn(5, 6, BLACK));
    piecesInGame_.push_back(new Pawn(6, 6, BLACK));
    piecesInGame_.push_back(new Pawn(7, 6, BLACK));
}
