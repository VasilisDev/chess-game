//
// Created by vasilis on 13/5/2019.
//

#include <iostream>
#include <sstream>
#include "include/Piece.h"


Piece::Piece(Color color, Piece::Type type) : _color(color), type(type) {}


Color Piece::getColor() const {
    return _color;
}

Piece::Type Piece::getType() const {
    return type;
}

string Piece::printType() const {
    switch (type) {
        case Piece::Type::KING:
            return "King";
        case Piece::Type::QUEEN:
            return "Queen";
        case Piece::Type::BISHOP:
            return "Bishop";
        case Piece::Type::KNIGHT:
            return "Knight";
        case Piece::Type::ROOK:
            return "Rook";
        case Piece::Type::PAWN:
            return "Pawn";
        //silence the warning: "control reaches end of non-void function"
        case Type::NONE:
            return "NULL";
    }
}

char Piece::convertTypeToChar(Type type) const {
    switch (type) {
        case Type::PAWN:
            return _color == Color::WHITE ? 'P' : 'p';
        case Type::KNIGHT:
            return _color == Color::WHITE ? 'N' : 'n';
        case Type::BISHOP:
            return _color == Color::WHITE ? 'B' : 'b';
        case Type::ROOK:
            return _color == Color::WHITE ? 'R' : 'r';
        case Type::QUEEN:
            return _color == Color::WHITE ? 'Q' : 'q';
        case Type::KING:
            return _color == Color::WHITE ? 'K' : 'k';
       // silence the warning : "control reaches end of non-void function"
        case Type::NONE:
            return '-';

    }
}

string Piece::printColor() const {
    if (Color::WHITE == _color)
        return "λευκού";
    else
        return "μαύρου";
}

