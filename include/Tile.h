//
// Created by vasilis on 13/5/2019.
//

#ifndef UNTITLED23_SQUARE_H
#define UNTITLED23_SQUARE_H


#include <memory>
#include "Piece.h"

class Piece;

class Tile {


public:
    Piece* getPiece() const;
    std::unique_ptr<Piece> setPiece(std::unique_ptr<Piece> piece);

protected:
    std::unique_ptr<Piece> piece_;


};


#endif //UNTITLED23_SQUARE_H
