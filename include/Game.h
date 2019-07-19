//
// Created by vasilis on 13/5/2019.
//

#ifndef UNTITLED23_GAME_H
#define UNTITLED23_GAME_H


#include <set>
#include <iostream>
#include "Board.h"
#include "Piece.h"


using namespace std;

class Game final{

public:
    static Game& newGame();
    Game(const Game&) = delete;
    Game(Game&&) = delete;
    Game& operator=(const Game&) = delete;
    Game& operator=(Game&&) = delete;
    void run();

private:
    bool startingNewGame = false;
    Game();
    ~Game();
    Board *board;
    void printLogo() const;
    string_view getColor(Color color) const;
    void printMenu() const;
    void printBoard();
    void testCheckMate();
    void testErrorCases();
    void testStaleMate();

};


#endif //UNTITLED23_GAME_H
