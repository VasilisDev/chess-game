//
// Created by vasilis on 13/5/2019.
//

#ifndef UNTITLED23_KNIGHT_H
#define UNTITLED23_KNIGHT_H


#include <iostream>
#include "Piece.h"
#include "Color.h"
#include "Board.h"


class Knight : public Piece {

public:
    explicit Knight(Color color);
    ~Knight() override = default;
    bool isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const override;
    char latin1Representation() const override {
        return _color == Color::WHITE ? 'N' : 'n';
    }
};


#endif //UNTITLED23_KNIGHT_H
