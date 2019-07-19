//
// Created by vasilis on 13/5/2019.
//

#ifndef UNTITLED23_KING_H
#define UNTITLED23_KING_H

#include "Color.h"
#include <iostream>
#include "Piece.h"
#include "Board.h"

class King : public Piece{

public:
    explicit King (Color color);
    ~King() override = default;
    bool isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const override;

    char latin1Representation() const override {
        return _color == Color ::WHITE?  'K' :  'k';
    }
};


#endif //UNTITLED23_KING_H
