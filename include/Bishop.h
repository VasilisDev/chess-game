//
// Created by vasilis on 13/5/2019.
//

#ifndef UNTITLED23_BISHOP_H
#define UNTITLED23_BISHOP_H


#include "Piece.h"
#include "Color.h"
#include "Board.h"
#include <iostream>

class Bishop : public Piece{
public:
    explicit Bishop(Color color);
    ~Bishop() override = default;
    bool isValidMove(const Board *board, const std::pair<int, int> &from, const std::pair<int, int> &to) const override;
    char latin1Representation() const override {
        return _color == Color::WHITE ? 'B' : 'b';
    }
};


#endif //UNTITLED23_BISHOP_H
