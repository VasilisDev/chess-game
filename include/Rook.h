//
// Created by vasilis on 13/5/2019.
//

#ifndef UNTITLED23_ROOK_H
#define UNTITLED23_ROOK_H


#include <iostream>
#include "Piece.h"
#include "Color.h"
#include "Board.h"

class Rook : public Piece {

public :
    explicit Rook(Color color);
    ~Rook() override = default;
    bool isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const override;
    char latin1Representation() const override {
        return _color == Color::WHITE ? 'R' : 'r';
    }
};


#endif //UNTITLED23_ROOK_H
