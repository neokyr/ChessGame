#include "Piece.h"
#include "Historic.h"

Piece *Historic::getMoving() const {
    return moving_;
}

const std::pair<int, int> &Historic::getFrom() const {
    return from_;
}

const std::pair<int, int> &Historic::getTo() const {
    return to_;
}

Piece *Historic::getDestroyed() const {
    return destroyed_;
}

Historic::Historic(Piece *moving, int x1, int y1, int x2, int y2, Piece *destroyed,  MoveType moveType,
                   Piece_Type promote) :
    moving_(moving),
    from_(pair<int, int>(x1,y1)),
    to_(pair<int, int>(x2,y2)),
    destroyed_(destroyed),
    moveType_(moveType),
    promote_(promote){}

MoveType Historic::getMoveType() const {
    return moveType_;
}

void Historic::setMoveType(MoveType moveType) {
    moveType_ = moveType;
}

Piece_Type Historic::getPromote() const {
    return promote_;
}
