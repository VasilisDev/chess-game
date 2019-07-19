//
// Created by vasilis on 13/5/2019.
//

#include <vector>
#include <sstream>
#include "include/Game.h"
#include <regex>
#include <iomanip>
#include <utils.h>


using ConstVector = const std::vector<std::string>;
using Pair        = std::pair<int,int>;

Game::Game() = default;

void Game::printMenu() const {
    cout << "Εντολές: [Κίνηση]Για κίνηση δίνετε τις συντεταγμένες ανάλογα με το που θέλετε να μετακινήσετε το πιόνι σας (π.χ. a2 a4)"<<"\n"<<
            "         [Έξοδος]πληκτρολογήστε \'exit\' για έξοδο"
                << "\n[Ιστορικό κινήσεων]για το ιστορικό κινήσεων πληκτρολογήστε  \'moves\' "
                   <<"\n[Δημιουργία καινούργιου παιχνιδιού] πληκτρολογήστε \'new game\'"
               << "\n [Φόρτωση προηγούμενου παιχνιδιού απο το αρχείο] load\n\n";
}


void Game::printLogo() const {
    cout << "    ======================================\n";
    cout << "       _____ _    _ ______  _____ _____\n";
    cout << "      / ____| |  | |  ____|/ ____/ ____|\n";
    cout << "     | |    | |__| | |__  | (___| (___ \n";
    cout << "     | |    |  __  |  __|  \\___ \\\\___ \\ \n";
    cout << "     | |____| |  | | |____ ____) |___) |\n";
    cout << "      \\_____|_|  |_|______|_____/_____/\n\n";
    cout << "    ======================================\n";
}

string_view Game::getColor(Color color) const {
    if (color == Color::WHITE)
        return "λευκού";
    else
        return "μαύρου";
}

void  Game::run() {

    Color c;
    board = new Board();
    //this regular expression validates the user's input !!
    std::regex input_regex("([a-h][1-8]\\s[a-h][1-8])");
    std::string input;

    printLogo();
    printMenu();
    cout << endl;
    printBoard();
    cout << endl;
       static int movenumber = 0;
        while (!board->isGameIsFinished()) {
            c = board->getTurn();
            cout << "Είναι σειρά του " << getColor(c) << '\n';
            cout << "Παρακαλώ δώστε τις συντεταγμένες χωρισμένες με κενό (π.χ. a2 a4)!" << endl;
            getline(std::cin, input);
            if (input == "exit") {
                board->setGameIsFinished(true);
            } else if (input == "moves") {
                board->printMovesHistory();
            }else if (input == "test checkMate") {
                if(movenumber > 0){
                    cerr<<"Έχετε ήδη αρχίσει να παίζετε δεν μπορείτε να πραγματοποιήσετε αυτή την είσοδο!"<<endl;
                }else
                  this->testCheckMate();
            }
            else if (input == "new game") {
                delete  board;
                board = new Board();
                movenumber=0;
                this->startingNewGame = true;
                this->printBoard();
            }
            else if(input ==  "test errorCases") {
                if(movenumber > 0){
                    cerr<<"Έχετε ήδη αρχίσει να παίζετε δεν μπορείτε να πραγματοποιήσετε αυτή την είσοδο!"<<endl;
                }else
                  this->testErrorCases();
            }
            else if(input ==  "test staleMate") {
                if(movenumber > 0){
                    cerr<<"Έχετε ήδη αρχίσει να παίζετε δεν μπορείτε να πραγματοποιήσετε αυτή την είσοδο!"<<endl;
                }else
                  this->testStaleMate();
            }
            else if(input == "load") {
                if(movenumber > 0){
                    cerr<<"Έχετε ήδη αρχίσει να παίζετε δεν μπορείτε να φορτώσετε προηγούμενο παιχνίδι!"<<endl;
                }else {
                    board->LoadFromFile(R"(C:\Users\vasilis\CLionProjects\untitled23\board.txt)");
                    board->ReadFromFileLastTurn(R"(C:\Users\vasilis\CLionProjects\untitled23\lastTurn.txt)");
                    board->displayBoard();
                }
            }
            else if (std::regex_match(input, input_regex)) {
                std::istringstream is(input);
                //split the input coordinates
                ConstVector tokens = std::vector<std::string>(
                        std::istream_iterator<std::string>(is),
                        std::istream_iterator<std::string>());

                Pair from = Utils::Instance().parse(tokens[0]);    // convert substring to pair
                Pair to = Utils::Instance().parse(tokens[1]);        // convert substring to pair

                board->submitMove(from, to);
                movenumber+=1;

                }
                else {
                cerr << "[Σφάλμα]: Λάθος είσοδος!Ελέξτε ξανά τις συντεταγμένες που δώσατε!" << '\n';
            }
        }
    }

void Game::printBoard() {
    board->displayBoard();
}

Game &Game::newGame() {
    static Game newGame;
    return newGame;
}

void Game::testCheckMate() {

    board->submitMove(Utils::Instance().parse("e2"), Utils::Instance().parse("e4"));
    board->submitMove(Utils::Instance().parse("e7"), Utils::Instance().parse("e5"));
    board->submitMove(Utils::Instance().parse("g1"), Utils::Instance().parse("f3"));
    board->submitMove(Utils::Instance().parse("f7"), Utils::Instance().parse("f6"));
    board->submitMove(Utils::Instance().parse("f3"), Utils::Instance().parse("e5"));
    board->submitMove(Utils::Instance().parse("f6"), Utils::Instance().parse("e5"));
    board->submitMove(Utils::Instance().parse("d1"), Utils::Instance().parse("h5"));
    board->submitMove(Utils::Instance().parse("e8"), Utils::Instance().parse("e7"));
    board->submitMove(Utils::Instance().parse("h5"), Utils::Instance().parse("e5"));
    board->submitMove(Utils::Instance().parse("e7"), Utils::Instance().parse("f7"));
    board->submitMove(Utils::Instance().parse("f1"), Utils::Instance().parse("c4"));
    board->submitMove(Utils::Instance().parse("d7"), Utils::Instance().parse("d5"));
    board->submitMove(Utils::Instance().parse("c4"), Utils::Instance().parse("d5"));
    board->submitMove(Utils::Instance().parse("f7"), Utils::Instance().parse("g6"));
    board->submitMove(Utils::Instance().parse("h2"), Utils::Instance().parse("h4"));
    board->submitMove(Utils::Instance().parse("h7"), Utils::Instance().parse("h5"));
    board->submitMove(Utils::Instance().parse("d5"), Utils::Instance().parse("b7"));
    board->submitMove(Utils::Instance().parse("c8"), Utils::Instance().parse("b7"));
    board->submitMove(Utils::Instance().parse("e5"), Utils::Instance().parse("f5"));
    board->submitMove(Utils::Instance().parse("g6"), Utils::Instance().parse("h6"));
    board->submitMove(Utils::Instance().parse("d2"), Utils::Instance().parse("d4"));
    board->submitMove(Utils::Instance().parse("g7"), Utils::Instance().parse("g5"));
    board->submitMove(Utils::Instance().parse("f5"), Utils::Instance().parse("f7"));
    board->submitMove(Utils::Instance().parse("d8"), Utils::Instance().parse("e7"));
    board->submitMove(Utils::Instance().parse("h4"), Utils::Instance().parse("g5"));
    board->submitMove(Utils::Instance().parse("e7"), Utils::Instance().parse("g5"));
    board->submitMove(Utils::Instance().parse("h1"), Utils::Instance().parse("h5"));

}

void Game::testErrorCases() {

    board->submitMove(Utils::Instance().parse("e2"), Utils::Instance().parse("e5"));
    board->submitMove(Utils::Instance().parse("e7"), Utils::Instance().parse("e6"));
    board->submitMove(Utils::Instance().parse("d2"), Utils::Instance().parse("d4"));
    board->submitMove(Utils::Instance().parse("d7"), Utils::Instance().parse("d5"));
    board->submitMove(Utils::Instance().parse("f3"), Utils::Instance().parse("e5"));
    board->submitMove(Utils::Instance().parse("b1"), Utils::Instance().parse("c3"));
    board->submitMove(Utils::Instance().parse("f8"), Utils::Instance().parse("b4"));
    board->submitMove(Utils::Instance().parse("f1"), Utils::Instance().parse("d3"));
    board->submitMove(Utils::Instance().parse("b4"), Utils::Instance().parse("c3"));
    board->submitMove(Utils::Instance().parse("b2"), Utils::Instance().parse("c3"));
    board->submitMove(Utils::Instance().parse("h7"), Utils::Instance().parse("h6"));
    board->submitMove(Utils::Instance().parse("c1"), Utils::Instance().parse("a3"));
    board->submitMove(Utils::Instance().parse("b8"), Utils::Instance().parse("d7"));
    board->submitMove(Utils::Instance().parse("d1"), Utils::Instance().parse("e2"));
    board->submitMove(Utils::Instance().parse("d5"), Utils::Instance().parse("e4"));
    board->submitMove(Utils::Instance().parse("g8"), Utils::Instance().parse("f6"));
    board->submitMove(Utils::Instance().parse("e4"), Utils::Instance().parse("d3"));
    board->submitMove(Utils::Instance().parse("b7"), Utils::Instance().parse("b6"));
    board->submitMove(Utils::Instance().parse("e2"), Utils::Instance().parse("e6"));
    board->submitMove(Utils::Instance().parse("f7"), Utils::Instance().parse("e6"));
    board->submitMove(Utils::Instance().parse("d3"), Utils::Instance().parse("g6"));

}

void Game::testStaleMate() {

    board->submitMove(Utils::Instance().parse("e2"), Utils::Instance().parse("e3"));
    board->submitMove(Utils::Instance().parse("a7"),Utils::Instance().parse("a5"));
    board->submitMove(Utils::Instance().parse("d1"), Utils::Instance().parse("h5"));
    board->submitMove(Utils::Instance().parse("a8"), Utils::Instance().parse("a6"));
    board->submitMove(Utils::Instance().parse("h5"), Utils::Instance().parse("a5"));
    board->submitMove(Utils::Instance().parse("h7"), Utils::Instance().parse("h5"));
    board->submitMove(Utils::Instance().parse("h2"), Utils::Instance().parse("h4"));
    board->submitMove(Utils::Instance().parse("a6"), Utils::Instance().parse("h6"));
    board->submitMove(Utils::Instance().parse("a5"), Utils::Instance().parse("c7"));
    board->submitMove(Utils::Instance().parse("f7"), Utils::Instance().parse("f6"));
    board->submitMove(Utils::Instance().parse("c7"), Utils::Instance().parse("d7"));
    board->submitMove(Utils::Instance().parse("e8"), Utils::Instance().parse("f7"));
    board->submitMove(Utils::Instance().parse("d7"), Utils::Instance().parse("b7"));
    board->submitMove(Utils::Instance().parse("d8"), Utils::Instance().parse("d3"));
    board->submitMove(Utils::Instance().parse("b7"), Utils::Instance().parse("b8"));
    board->submitMove(Utils::Instance().parse("d3"), Utils::Instance().parse("h7"));
    board->submitMove(Utils::Instance().parse("b8"), Utils::Instance().parse("c8"));
    board->submitMove(Utils::Instance().parse("f7"), Utils::Instance().parse("g6"));
    board->submitMove(Utils::Instance().parse("c8"), Utils::Instance().parse("e6"));
}



Game::~Game() = default;
