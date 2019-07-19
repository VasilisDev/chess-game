#include <algorithm>
#include <codecvt>
#include <locale>
#include <iterator>
#include "include/utils.h"
#include "logger/Logger.h"
#include "include/Board.h"
#include "include/Bishop.h"
#include "include/Knight.h"
#include "include/Rook.h"
#include "include/Queen.h"
#include "include/King.h"
#include "include/Pawn.h"


using PairVector   =  std::vector<std::pair<int, int>>;
using MovePair     =  std::pair<std::pair<int, int>, std::pair<int, int>>;
using Pair         =  std::pair<int,int>;
using OptionalPair = std::optional< std::pair<int,int>>;
using namespace Errors;

Board::Board() : colorOfCurrentPlayer(Color::WHITE), errorCode(ErrorCode::SUCCESS), gameIsFinished(false),
                 capturedPiece(nullptr) {
    initTiles();
    initPawns();
    initRooks();
    initKnights();
    initBishops();
    initQueens();
    initKings();
}

/**
 * Display the board in algebraic notation.
 */
void Board::displayBoard() {

    int it = 1;
    int row = 8;
    std::cout << "   a   b   c   d   e   f   g   h" << '\n';
    for(auto& [key,value]: tiles)
    {
        if ((it - 1) % 8 == 0) {
            std::cout << " +---+---+---+---+---+---+---+---+" << endl;
            std::cout << row <<""<< "|";
        }
        //find by key in the tile map and return the piece object that places in that coordinate.
        const Piece *piece = tiles.find(key)->second->getPiece();
        if (piece == nullptr) {
            std::cout << "   |";
        } else {
            //polymorphic virtual function that displays our pieces
            std::cout <<" "<< piece->latin1Representation()<<" ";
            std::cout << "|";
        }
        if (it % 8 == 0) {
            std::cout << row;
            row--;
            std::cout << '\n';
        }
        it++;
    }
    std::cout << " +---+---+---+---+---+---+---+---+" << endl;
    std::cout << "   a   b   c   d   e   f   g   h" << '\n';
}

/**
 * firstly , we must initialize out map and after place every tile with the specific piece.
 */
void Board::initTiles() {
    for (int row:{0,1,2,3,4,5,6,7}) {
        for (int column:{0,1,2,3,4,5,6,7}) {
            tiles.insert({make_pair(row, column), make_unique<Tile>()});
        }
    }
}

/* Creates a pair of coordinates and an object of piece and place them in map that represents the board */
void Board::initPawns() {

    // White pawns
    for (int column:{0,1,2,3,4,5,6,7})
        setPiece(make_pair(6, column), make_unique<Pawn>(Color::WHITE));

    // Black pawns
    for (int column:{0,1,2,3,4,5,6,7})
        setPiece(make_pair(1, column), make_unique<Pawn>(Color::BLACK));
}

/* Creates a pair of coordinates and an object of piece and place them in map that represents the board */
void Board::initRooks() {
    // White Rooks
    setPiece(make_pair(7, 0), make_unique<Rook>(Color::WHITE));
    setPiece(make_pair(7, 7), make_unique<Rook>(Color::WHITE));

    // Black Rooks
    setPiece(make_pair(0, 0), make_unique<Rook>(Color::BLACK));
    setPiece(make_pair(0, 7), make_unique<Rook>(Color::BLACK));
}

/* Creates a pair of coordinates and an object of piece and place them in map that represents the board */
void Board::initKnights() {
    // White Knights
    setPiece(make_pair(7, 1), make_unique<Knight>(Color::WHITE));
    setPiece(make_pair(7, 6), make_unique<Knight>(Color::WHITE));

    // Black Knights
    setPiece(make_pair(0, 1), make_unique<Knight>(Color::BLACK));
    setPiece(make_pair(0, 6), make_unique<Knight>(Color::BLACK));
}

/* Creates a pair of coordinates and an object of piece and place them in map that represents the board */
void Board::initBishops() {
    // White Bishops
    setPiece(make_pair(7, 2), make_unique<Bishop>(Color::WHITE));
    setPiece(make_pair(7, 5), make_unique<Bishop>(Color::WHITE));

    // Black Bishops
    setPiece(make_pair(0, 2), make_unique<Bishop>(Color::BLACK));
    setPiece(make_pair(0, 5), make_unique<Bishop>(Color::BLACK));
}

/* Creates a pair of coordinates and an object of piece and place them in map that represents the board */
void Board::initQueens() {
    // White Queen
    setPiece(make_pair(7, 3), make_unique<Queen>(Color::WHITE));

    // Black Queen
    setPiece(make_pair(0, 3), make_unique<Queen>(Color::BLACK));
}

/* Creates a pair of coordinates and an object of piece and place them in map that represents the board */
void Board::initKings() {
    // White King
    setPiece(make_pair(7, 4), make_unique<King>(Color::WHITE));

    // Black King
    setPiece(make_pair(0, 4), make_unique<King>(Color::BLACK));
}


std::unique_ptr<Piece> Board::setPiece(const pair<int, int> &coords, unique_ptr<Piece> piece) {
    return tiles[coords]->setPiece(std::move(piece));
}

/**
 * @return Color .The {@link#Color} of the current player
 */
Color Board::getTurn() {
    if (colorOfCurrentPlayer == Color::WHITE)
        return Color::WHITE;
    else
        return Color::BLACK;
}
/**
 * Prints the current turn
 * @return string_view.Prevent copies of that string.Make it constant using c++17 string_view
 */
string_view Board::printTurn() {

    if (colorOfCurrentPlayer == Color::WHITE)
        return "λευκού";
    else
        return "μαύρου";
}
/**
 * @param coords
 * @return true if coordinates are in bound otherwise returns false.
 */
bool Board::isValidCoordinates(const Pair &coords) const {
    return !(coords.first < 0 || coords.first > 7);
}

/**
 * Checks if a position is null.
 * @param coords
 * @return true if the position is empty else returns false
 */
bool Board::isEmptyPosition(const Pair &coords) const {
    return getPiece(coords) == nullptr;
}

/**
 * @param to Destination coordinate
 * @param color Current player color
 * @return true if destination position is not empty and is not the same color with current's player color
 */
bool Board::isOccupierPiece(const Pair &to, Color color) const {
    const Piece *piece = getPiece(to);
    return !isEmptyPosition(to) && (piece->getColor() != color);
}

/**
 * Uses the find stl algorithm for map container.
 * Clients don't need to free memory due to using of smart pointers
 * @param coords .The coordinates of the desired location.
 * @return a pointer to a piece object according to coordinates.
 */
Piece *Board::getPiece(const Pair &coords) const {
    //look up in the mapper.Complexity O(logN)
    return tiles.find(coords)->second->getPiece();
}

/**
 * File represents a column.So we need to traverse in the column to see if it is empty.
 * @param from Source coordinate
 * @param to  Destination coordinate
 * @return true if the file is clear , otherwise return false.
 */
bool Board::isFileClear(const Pair &from, const Pair &to) const {
    //we need to traverse a column.
    if (!isHorizontalMove(from, to))
        return false;

    int rankChange = 0;
    //if traverse from white left to white right .It's obvious that  moves  horizontally ,so increase rankChange by one
    if (isMovingEast(from, to))
        rankChange = 1;
    //otherwise decrease the rankChange by one
    else
        rankChange = -1;

    Pair middle = from;
    //we want to see if  there is a piece next to source coordinate.So increase by one that column.
    middle.second += rankChange;

    //we achieve that here!We traverse the path while it is empty.If we find a piece in that path, then return false.
    while (middle != to) {
        if (!isEmptyPosition(middle))
            return false;
        //go deeper
        middle.second += rankChange;
    }
    //otherwise the path file is empty return true.
    return true;
}

/**
 * Rank represents rows.So we need to traverse a row to see if it is empty.
 * @param from Source coordinate
 * @param to   Destination coordination
 * @return true if the rank is clear , otherwise returns false.
 */
bool Board::isRankClear(const Pair &from, const Pair &to) const {
    if (!isVerticalMove(from, to))
        return false;

    int fileChange = 0;
    //if black moves to white side increase fileChange by one
    if (isMovingSouth(from, to))
        fileChange = 1;
    else
        fileChange = -1; // otherwise decrease that variable

    Pair middle = from;
    // in order to check if the row is empty we need to increase by one the value of that row.
    middle.first += fileChange;

    //traverse the row path until it is empty.If the row path is not empty return false
    while (middle != to) {
        if (!isEmptyPosition(middle))
            return false;
        //go deeper
        middle.first += fileChange;
    }
    // otherwise row path is empty return true
    return true;
}

/**
 * @param from Source coordinate
 * @param to Destination coordinate
 * @return true if a specific diagonal path is empty, othrwise returns false.
 */
bool Board::isDiagonalClear(const Pair &from, const Pair &to) const {

    //check firstly if the move is not diagonal.
    if (!isDiagonalMove(from, to))
        return false;

    int fileChange = 0;
    int rankChange = 0;
    //black moves to white side ?Then increase fileChange by one
    if (isMovingSouth(from, to))
        fileChange = 1;
    else
        fileChange = -1; // otherwise decrease fileChange by one

    //if traverse from white left to white right .It's obvious that  moves  horizontally ,so increase rankChange by one
    if (isMovingEast(from, to))
        rankChange = 1;
    else
        rankChange = -1;//otherwise decrease rankChange by one


    Pair middle = from;
    //increase row by fileChange
    middle.first += fileChange;
    //increase column by rankChange
    middle.second += rankChange;

    //traverse that diagonal path and check if there is a piece on it!If there is then return false.
    while (middle != to) {
        if (!isEmptyPosition(middle))
            return false;
        //go deeper
        middle.first += fileChange; //increase row by fileChange
        middle.second += rankChange;//increase column by rankChange
    }
    //Everything ok.Path is clear , so return true.
    return true;
}

void Board::submitMove(const Pair &from, const Pair &to) {
    errorCode = ErrorCode::SUCCESS;
    static int moveNumber = 1;
    WriteToFileLastTurn(R"(C:\Users\vasilis\CLionProjects\untitled23\lastTurn.txt)");


    /**
     * check firstly if the movement is valid
     * @see {@link#isLegalMove(const Pair& from,Const Pair& to)}
     */
    if (!isLegalMove(from, to)) {
        printError(from, to);
        return;
    }
    //if everything is ok
    //move the piece to destination tile
    movePiece(from, to);
        //check if own king is in check!
        if (isInCheck(colorOfCurrentPlayer)) {
            undoLastMove();
            errorCode = ErrorCode::ERROR_OWN_KING_IN_CHECK;
            printError(from, to);
            return;
        }
    //normalize the word!
    string player_turn= getPiece(to)->printColor() =="λευκού" ? "λευκός" : "μαύρος";
    //valid move so give to user information about the event
    cout <<"Ο "<<player_turn<<" "
         << getPiece(to)->printType() << " κινήθηκε από " << Utils::Instance().toAlgebraic(from) << " προς " << Utils::Instance().toAlgebraic(to);

    /**
     * if capturedPiece contained a pointer to piece then a piece captured another.
     * So gives the specific information to user.
     */
    if (capturedPiece != nullptr)
    {
        string playerColor;
        cout << " αιχμαλώτισε ";

        if (colorOfCurrentPlayer == Color::WHITE)
            cout << "του μαυρού το πιόνι ";
        else
            cout << "του λευκού το πιόνι ";
        cout << capturedPiece->printType();
    }
    cout << endl;

#ifdef _WIN32
        SaveToFile(R"(C:\Users\vasilis\CLionProjects\untitled23\board.txt)");
#else
       SaveToFile(R"(/home/board.txt)");
#endif

    if (colorOfCurrentPlayer == Color::WHITE && moveNumber != 1) {

#ifdef _WIN32
        LoadFromFile(R"(C:\Users\vasilis\CLionProjects\untitled23\board.txt)");
#else
        LoadFromFile(R"(/home/board.txt)");
#endif
        displayBoard();
    } else
        displayBoard();

    if (getPiece(to)->getType() == Piece::Type::PAWN) {
        /**
         *If for pawn is not the first move we must set the attribute {@link#firstMove}.
         *In order to change set {@link#firstMove} false we must downcast to {@link#Class#Pawn} from base Class.
         *Polymorphism gives us the ability to downcast from the base class to derived class using dynamic_cast<>
         */
        dynamic_cast<Pawn*>(getPiece(to))->setFirstMove(false);
    }
    /**
     * this is a temporary pointer so when a new move submitted set this nullptr
     */
    if (capturedPiece != nullptr) {
        capturedPiece = nullptr;
    }
    changeTurn();
    moveNumber = moveNumber + 1;
    // is in Check?
    if (isInCheck(colorOfCurrentPlayer)) {
        //has more valid moves?
        //so he is in check
        // otherwise in checkmate
        if (hasAnyValidMove(colorOfCurrentPlayer)) {
            cout <<"Η σειρά είναι του " <<printTurn().data() << " που είναι σε check" << endl;
            return;
        } else {
            cout <<"Η σειρά είναι του "<< printTurn().data() << " που είναι σε checkmate" << endl;
            cout<<"Το παιχνίδι μόλις τελειώσε!"<< endl;
            gameIsFinished = true;
            return;
        }
    }

    /**
     * if there is no more valid moves then we have a stalemate for this player and the game finishes!
     */
    if (!hasAnyValidMove(colorOfCurrentPlayer)) {
        cout<<"Η σειρά είναι του " << printTurn().data() << " που είναι σε stalemate" << endl;
        cout<<"Το παιχνίδι μόλις τελειώσε!"<< endl;
        gameIsFinished = true;
        return;
    }
#ifdef _WIN32
    SaveToFile(R"(C:\Users\vasilis\CLionProjects\untitled23\board.txt)");
#else
    SaveToFile(R"(/home/board.txt)");
#endif

    WriteToFileLastTurn(R"(C:\Users\vasilis\CLionProjects\untitled23\lastTurn.txt)");
}


/**
 * Check if the movement is vertical.How we achieve that? Imagine tha we have a numerical board like this,so if the the second
 * value of the destination pair is equal to source pair then piece moves vertical.
 * @param from Source coordinate
 * @param to  Destination coordinate
 * @return true if the movement is vertical , otherwise returns false.
 */
bool Board::isVerticalMove(const Pair &from, const Pair &to) const {
    return from.second == to.second;
}

/**
 * Check if the movement is horizontal.If the the second value of the destination pair is equal to source pair then piece moves horizontal.
 * @param from  Source coordinate
 * @param to    Destination coordinate
 * @return true if the movement is horizontal , else returns false.
 */
bool Board::isHorizontalMove(const Pair &from, const Pair &to) const {
    return from.first == to.first;
}

/**
 * If the vertical difference is equal to horizontal difference then we have diagonal movement.
 * @param from Source coordinate
 * @param to Destination coordinate
 * @return true if the movement is diagonal, else return false.
 */
bool Board::isDiagonalMove(const Pair &from, const Pair &to) const {
    int verticalDifference = to.first - from.first;
    int horizontalDifference = to.second - from.second;
    return abs(verticalDifference) == abs(horizontalDifference);
}

/**
 * Uses the difference of every movement in our chess game world
 * @param from Source coordinate
 * @param to Destination coordinate
 * @return an integer that represents the the move length
 */
int Board::getMoveLength(const Pair &from, const Pair &to) const {
    if (isVerticalMove(from, to)) {
        return abs(to.first - from.first);
    } else if (isHorizontalMove(from, to)) {
        return abs(to.second - from.second);
    } else if (isDiagonalMove(from, to)) {
        return abs(to.first - from.first);
    } else {
        return -1;
    }
}

/**
 * A function that validates the movement before submit it.
 * @param from Source piece
 * @param to Destination piece
 * @return true if the movement is valid according to chess rules{@link <a href="https://en.wikipedia.org/wiki/Rules_of_chess">chess rules</a>}.
 * Otherwise returns false and call the {@link#printError(const Pair &from, const Pair &to)} to inform the user about the error.
 */
bool Board::isLegalMove(const Pair &from, const Pair &to) {
    //fetch the object that places on from coordinate
    Piece *fromPiece = getPiece(from);

    //Is the source empty?
    if(isEmptyPosition(from))
    {
        errorCode = ErrorCode::ERROR_NO_PIECE_AT_SOURCE;
        return false;
    }
    //Is source out of bound?
    if (!isValidCoordinates(from))
    {
        errorCode = ErrorCode::ERROR_INVALID_INPUT_SOURCE;
        return false;
    }
    //Is destination out of bound?
    if (!isValidCoordinates(to))
    {
        errorCode = ErrorCode::ERROR_INVALID_INPUT_DESTINATION;
        return false;
    }
    //Are both source and destination out of bounds?
    if (!isValidCoordinates(from) && !isValidCoordinates(to))
    {
        errorCode = ErrorCode::ERROR_INVALID_INPUT_SOURCE_AND_DESTINATION;
        return false;
    }
    //User tries to access an occupier's piece?
    if (fromPiece->getColor() != colorOfCurrentPlayer)
    {
        errorCode = ErrorCode::ERROR_WRONG_PLAYER;
        return false;
    }
    //Uses the same coordinates?What?
    if (to == from)
    {
        errorCode = ErrorCode::ERROR_SOURCE_AND_DESTINATION_SAME;
        return false;
    }
    //Is try to access a friendly piece?
    if (!isEmptyPosition(to) &&
        !isOccupierPiece(to, fromPiece->getColor()))
    {
           errorCode = ErrorCode::ERROR_FRIENDLY_PIECE_AT_DESTINATION;
           return false;
    }
    //Is an invalid move for a piece?
    if (!fromPiece->isValidMove(this, from, to))
    {
         errorCode = ErrorCode::ERROR_INVALID_PIECE_MOVE;
         return false;
    }
    //that's ok make move!
    return true;
}

/***
 *  swap the current turn.
 */
void Board::changeTurn() {
    if (colorOfCurrentPlayer == Color::BLACK) {
        colorOfCurrentPlayer = Color::WHITE;
    }
    else {
        colorOfCurrentPlayer = Color::BLACK;
    }
}

/***
 * prints the error according to {@link#ErrorCode}.
 * @param from Source piece
 * @param to Destination piece
 */
void Board::printError(const Pair &from, const Pair &to) const {
    Piece *piece = getPiece(from);
    switch (errorCode) {
        case ErrorCode::ERROR_NO_PIECE_AT_SOURCE :
            Logger::instance().log("Δεν υπάρχει κανένα πιόνι στο σημείο " + Utils::Instance().toAlgebraic(from) + " !" + "\n",
                                   Logger::LogLevel::Error);
            break;
        case ErrorCode::ERROR_INVALID_INPUT_DESTINATION :
            Logger::instance().log("Το προοριζόμενο σημείο " + Utils::Instance().toAlgebraic(to) + " είναι πέρα απο τα όρια!" + "\n",
                                   Logger::LogLevel::Error);
            break;
        case ErrorCode::ERROR_INVALID_INPUT_SOURCE :
            Logger::instance().log("Το σημείο πηγή " + Utils::Instance().toAlgebraic(from) + " είναι πέρα απο τα όρια!" + "\n",
                                   Logger::LogLevel::Error);
            break;
        case ErrorCode::SUCCESS:
            break;
        case ErrorCode::ERROR_GAME_HAS_FINISHED:
            Logger::instance().log("Το παιχνίδι μόλις τελείωσε!" + '\n',
                                   Logger::LogLevel::Info);
            break;
        case ErrorCode::ERROR_WRONG_PLAYER:
            Logger::instance().log("Δεν είναι σειρά του " + piece->printColor() + " να παίξει!" + "\n",
                                   Logger::LogLevel::Error);
            break;
        case ErrorCode::ERROR_SOURCE_AND_DESTINATION_SAME:
            Logger::instance().log("Πληκτρολογήσατε το σημείο πηγής " + Utils::Instance().toAlgebraic(from) + " και το σημείο προορισμού "
                                   + Utils::Instance().toAlgebraic(to) + ". Δεν πρέπει να είναι ίδια!" + "\n", Logger::LogLevel::Error);
            break;
        case ErrorCode::ERROR_FRIENDLY_PIECE_AT_DESTINATION:
            Logger::instance().log("Δεν μπορείτε να μετακινηθείτε από " + Utils::Instance().toAlgebraic(from)

                                   + " προς " + Utils::Instance().toAlgebraic(to)
                                   + " επειδή υπάρχει φιλικό πιόνι στο σημείο " + Utils::Instance().toAlgebraic(to) + "\n",
                                   Logger::LogLevel::Error);
            break;
        case ErrorCode::ERROR_INVALID_PIECE_MOVE:
            Logger::instance().log("Αυτή είναι μία λάθος κίνηση για αυτό το πιόνι.Παρακαλώ δοκιμάστε ξανά!\n", Logger::LogLevel::Error);
            break;
        case ErrorCode::ERROR_OWN_KING_IN_CHECK:

            Logger::instance().log("Το να μετακινηθείτε " + getPiece(from)->printColor() + "'s "
                                   + getPiece(from)->printType() + " από " + Utils::Instance().toAlgebraic(from) + " to "
                                   + Utils::Instance().toAlgebraic(to) + " οδηγεί τον βασιλιά σε check!", Logger::LogLevel::Error);
            break;
        case ErrorCode::ERROR_INVALID_INPUT_SOURCE_AND_DESTINATION:
            Logger::instance().log("Το σημείο πηγής " + Utils::Instance().toAlgebraic(from)
                                   + " και το σημείο προορισμού " + Utils::Instance().toAlgebraic(to) + " είναι πέρα απο τα όρια!" + "\n",
                                   Logger::LogLevel::Error);
    }
}

/**
 * from white left to white right
 */
bool Board::isMovingEast(const Pair &from, const Pair &to) const {
    return from.second < to.second;
}

/**
 * from black side to white side
 */
bool Board::isMovingSouth(const Pair &from, const Pair &to) const {
    return from.first < to.first;
}

/**
 * @param from Source piece
 * @param to Destination piece
 * @param piece A piece pointer which used in order to check if the movement is forward.To do this we need to know the color of the player
 * because of the difficulty that provides the numerical representation of coordinates
 * @return
 *  <ul>
 *    <li><h1>true</h1>
 *         <ul>
 *            <li>If for {@link#Color::BLACK} the destination column is greater than the source column.
 *             Valid example 10 -> 20</li>
 *            <li>If for {@link#Color::WHITE} the destination column is greater than the source column.
 *            Valid example 60 -> 50</li>
 *        </ul>
 *     </li>
 *     <li><h2>false</h2>
 *          <ul>
 *            <li>If for {@link#Color::BLACK} the destination column is lesser than the source column.
 *             We need to go from coordination 10  ->  20 not from 10 -> 11 this is not a forward movement.</li>
 *            <li>If for {@link#Color::WHITE} the destination column is greater than the source column.
 *               We need to go from coordination 60  ->  50 not from 60 -> 61 this is not a forward movement.</li>
 *            </li>
 *          </ul>
 *      </li>
 *   </ul>
 * */

bool Board::isForwardMove(const Pair &from, const Pair &to, const Piece *piece) const {
    Color pieceColor = piece->getColor();
    if (pieceColor == Color::BLACK && from.first < to.first) {
        return true;
    } else return pieceColor == Color::WHITE && from.first > to.first;
}
/**
 * Cases to finished the game are checkmate and stalemate.
 * @return true if the game has finished.
 */

bool Board::isGameIsFinished() const {
    return gameIsFinished;
}

/**
 * A function that returns an optional pair of king's location for a specific player
 * @param color
 * @return std::optional<std::pair<int,int> .Returns an optional location of king piece for a specific player.
 * If no king piece find returns nullopt.
 * In reality, optional prevents us from nullptr references which crash our programs.
 * @see <a href="https://en.cppreference.com/w/cpp/utility/optional">std::optional</a>
 */
OptionalPair Board::getLocationOfKing(Color color) const {
    for(auto& tile: tiles){
        Piece *piece = tile.second->getPiece();
        // for  a specific player return the coordinate of the king.If there are not ( for any reason ) instance piece of king
        // return nullopt and prevent nullptr reference
        if (piece != nullptr && piece->getColor() == color && piece->getType() == Piece::Type::KING) {
            return tile.first;
        }
    }
    return nullopt;
}

/**
 * A function that returns all the non empty locations for a specific player
 * @param color The
 * @return std::vector<std::pair<int,int>> which contains the locations for every piece on the board by desired color.
 */
PairVector Board::getLocationsByColor(Color color) const {
    PairVector pieceLocations;
    //first dynamically reserve capacity for vector
    pieceLocations.reserve(tiles.size());
    for(auto& [key,value] :tiles){
        Piece *piece = value->getPiece();
        if (!isEmptyPosition(key) && piece->getColor() == color) {
            pieceLocations.push_back(key);
        }
    }
    return pieceLocations;
}


/***
 * It returns all locations that take place on board
 * @return std::vector<std::pair<int,int>> which contains all locations for every piece on the board.
 */
PairVector Board::getAllLocations() const {
    PairVector pieceLocations;
    //reserve size for the vector of pairs for performance purposes.
    pieceLocations.reserve(tiles.size());
    /**
     * iterate over the {@link#this->tiles} mapper using modern c++17 structured binding.
     * @see <a href="https://en.cppreference.com/w/cpp/language/structured_binding">structures binding</a>.
     */
    for(auto& [key,value] :tiles){
        pieceLocations.push_back(key);
    }
    return pieceLocations;
}

/**
 *
 * @param defendingColor Defendings color that used to fetch his king locations in order to check if one of them or both are in check
 * @return true if is in check , otherwise returns false
 */
bool Board::isInCheck(Color defendingColor) {
    //holds the color of attacker
    Color attackingColor;
    if (defendingColor == Color::WHITE) {
        attackingColor = Color::BLACK;
    } else {
        attackingColor = Color::WHITE;
    }
    //return king location by defenders color
    OptionalPair kingLocation = getLocationOfKing(defendingColor);
    // return all piece locations of attacking color
    PairVector pieceLocations = getLocationsByColor(attackingColor);
    //if king piece is present
    if(kingLocation) {
        for (auto &piece: pieceLocations) {
            //access the tiles mapper by piece location of attacking color which represents the key and check
            // if a move for attacking color that sets the defending's color king in check return true , otherwise false.
            if (tiles[piece]->getPiece()->isValidMove(this, piece, kingLocation.value())) {
                return true;
            }
        }
    }
    return false;
}

/**
 *
 * @param defendingColor Defender's color
 * @return true if defending color has any valid move , otherwise returns false
 */
bool Board::hasAnyValidMove(Color defendingColor) {
    //get locations by defending's color
    PairVector pieceLocations = getLocationsByColor(defendingColor);
    //get all locations
    PairVector locations = getAllLocations();
    // for every piece location of defending color
    for (auto const &pieceLocation : pieceLocations) {
        // for every piece location
        for (auto const &location : locations) {
            // check if is legal move from defender's location to every location on the board and if for every piece  move is valid
            Piece* piece = getPiece(pieceLocation);
            if (isLegalMove(pieceLocation, location) &&
                piece->isValidMove(this, pieceLocation, location)) {
                    //then make move in order to check if this movement sets his king in check
                movePiece(pieceLocation, location);
                // If player is no longer in check, undo move and return true.
                if (!isInCheck(defendingColor)) {
                    undoLastMove();
                    return true;
                }
                // if player was in check undo last move and try with another move
                undoLastMove();
            }
        }
    }
    return false;
}

/**
 * this function undo last move from the board and pops back the move from list history!
 */
void Board::undoLastMove() {
    //return if moves history is empty
    if (movesHistory.empty()) return;
    MovePair lastMove = movesHistory.back();
    /*swap the values*/
    // set lastMove.second (which is represent the to coordinate )
    // with the lastMove.first ( which represents the from coordinate ) and set lastMove.second=nullptr
    setPiece(lastMove.first, setPiece(lastMove.second, nullptr));
    //set lastMove.second = capturedPiece(make capturedPiece right hand side value using std::move c++11)
    setPiece(lastMove.second, std::move(capturedPiece));
    //and then set the captured piece null
    capturedPiece = nullptr;
    //set false the bitset for this piece.We make an undo command!
    moved[lastMove.second.first][lastMove.second.second] = false;
    //delete the last move!
    movesHistory.pop_back();
}

/**
 *  Move a piece from one spot to another ,save it in a list of moves history
 *  and set the value in moved bitset true for this coordinate
 * @param from source piece
 * @param to destination piece
 */
void Board::movePiece(const Pair &from, const Pair &to) {
    // this piece has moved so set for this coordinate true in the bitset
    moved[to.first][to.second] = true;
    //return the piece that is in "destination coordinates and set this coordinate to nullptr
    capturedPiece = setPiece(to, nullptr);
    //set the destination piece = source piece and then set the location of source = nullptr
    setPiece(to, setPiece(from, nullptr));
    // emplace back the movement
    movesHistory.emplace_back(from, to);
}

/**
 * Shows all available movements if the list of them are not empty.
 */
void Board::printMovesHistory() const{
    if (movesHistory.empty()) {
        cout << "Δεν υπάρχουν κινήσεις εως τώρα!" << endl;
        return;
    }
    std::for_each(movesHistory.begin(),movesHistory.end(),[&](auto &move)
    {
        cout << "Από το σημείο " << Utils::Instance().toAlgebraic(move.first) << " στο σημείο " << Utils::Instance().toAlgebraic(move.second) << '\n';
    });
}

/**
 * Saves the piece first letter , the coordinates of this piece, and 1 if this piece has moved or 0 if it hasn't moved.
 * If a coordinate on board is nullptr saves it as '-' .Helps to parse the file easier.
 * {@link#this->InputOutPutHelper} is a helper struct.Used to stored the values that are going to write on the stream.
 * @param fileName The name of the binary file tha we want to save our data
 */
void Board::SaveToFile(string fileName) {
    ofstream savedFile(fileName, std::ios::binary | std::ios::out | std::ios::in);
    if (!savedFile.is_open()) { cerr<< "Σφάλμα κατά την διάρκεια του ανοίγματος του αρχείου!"<<endl; return;}
        try {
            for (int row :{0, 1, 2, 3, 4, 5, 6, 7}) {
                for (int column :{0, 1, 2, 3, 4, 5, 6, 7}) {
                    Pair location = std::make_pair(row, column);

                    if (Piece *piece = getPiece(location);!isEmptyPosition(location)) {
                        Piece::Type type = piece->getType();
                        io.moved = moved[row][column];
                        io.posX = row;
                        io.posY = column;
                        io.piece = piece->convertTypeToChar(type);
                        savedFile << io;
                    } else {
                        io.piece = '-';
                        io.moved = false;
                        io.posX = row;
                        io.posY = column;
                        savedFile << io;
                    }
                }
            }
        }
        catch(std::ios_base::failure& ex) {
            cerr<<ex.what()<<endl;
    }
    savedFile.close();
}

/**
 * Read from file and set on board the pieces that has moved and nullptr values.
 * {@link#this->InputOutPutHelper} is a helper struct.Used to stored the values that are going to read from the stream
 * @param fileName Filename that we want to read from
 */
void Board::LoadFromFile(const string fileName) {
    ifstream loadedFile(fileName, std::ios::binary | std::ios::in);
    //something went wrong while opening the file
    if (!loadedFile.is_open()) { cerr<<"Σφάλμα κατά την διάρκεια του ανοίγματος του αρχείου!"<<endl; return;}
        try{
            char piece;
            int posX,posY;
            bool hasMoved;
            for (int row :{0, 1, 2, 3, 4, 5, 6, 7}) {
                for (int column :{0, 1, 2, 3, 4, 5, 6, 7}) {
                    loadedFile.read(&piece, sizeof(piece));
                    loadedFile.read(reinterpret_cast< char *>(&posX), sizeof(posX));
                    loadedFile.read(reinterpret_cast< char *>(&posY), sizeof(posY));
                    loadedFile.read(reinterpret_cast< char *>(&hasMoved), sizeof(hasMoved));

                    Pair location = make_pair(row,column);
                    if (piece == '-') {
                        setPiece(location, nullptr);
                        this->moved[row][column] = false;
                    } else {
                        this->moved[row][column] = hasMoved;
                        updateBoard(location,piece);
                    }
                  }
               }
             } catch (std::ios_base::failure &e){
             cerr<<e.what()<<endl;
        }
        loadedFile.close();
}

/**
 *
 * @param ofile output file stream that  we will write our data
 * @param d Helper struct that holds are data that we will write on stream
 * @return std::ofstream reference
 */
std::ofstream &operator<<(std::ofstream &ofile, Board::InputOutPutHelper const &d) {

    ofile.write(&d.piece, sizeof(d.piece));
    /**
     * cast from pointer{@link#this->InputOutPutHelper#d} to const char*.
     */
    ofile.write(reinterpret_cast<const char *>(&d.posX), sizeof(d.posX));
    ofile.write(reinterpret_cast<const char *>(&d.posY), sizeof(d.posY));
    ofile.write(reinterpret_cast<const char *>(&d.moved), sizeof(d.moved));
    return ofile;
}

void Board::setGameIsFinished(bool gameIsFinished) {
    Board::gameIsFinished = gameIsFinished;
}

/**
 * Update the board when we want to load it from the file.
 * @param coords
 * @param piece
 */
void Board::updateBoard(const std::pair<int, int> &coords, const char &piece) {

    switch(piece){
        case 'r':
            setPiece(coords, make_unique<Rook>(Color::BLACK));
            break;
        case 'n':
            setPiece(coords, make_unique<Knight>(Color::BLACK));
            break;
        case 'b':
            setPiece(coords, make_unique<Bishop>(Color::BLACK));
            break;
        case 'q':
            setPiece(coords, make_unique<Queen>(Color::BLACK));
            break;
        case 'k':
            setPiece(coords, make_unique<King>(Color::BLACK));
            break;
        case 'p':
            setPiece(coords, make_unique<Pawn>(Color::BLACK));
            if(this->moved[coords.first][coords.second])
                dynamic_cast<Pawn*>(getPiece(coords))->setFirstMove(false);
            break;
        case 'R':
            setPiece(coords, make_unique<Rook>(Color::WHITE));
            break;
        case 'N':
            setPiece(coords, make_unique<Knight>(Color::WHITE));
            break;
        case 'B':
            setPiece(coords, make_unique<Bishop>(Color::WHITE));
            break;
        case 'Q':
            setPiece(coords, make_unique<Queen>(Color::WHITE));
            break;
        case 'K':
            setPiece(coords, make_unique<King>(Color::WHITE));
            break;
        case 'P':
            setPiece(coords, make_unique<Pawn>(Color::WHITE));
            if(this->moved[coords.first][coords.second])
                dynamic_cast<Pawn*>(getPiece(coords))->setFirstMove(false);
            break;
        default:break;
    }
}

void Board::WriteToFileLastTurn(const string &filename) {

    ofstream savedFile(filename,  std::ios::out | std::ios::trunc);
    if (!savedFile.is_open()) { cerr<< "Σφάλμα κατά την διάρκεια του ανοίγματος του αρχείου!"<<endl; return;}
    try {
          string name = this->printTurn() == "μαύρου" ? "black" : "white";
          cout<<name;
          savedFile << name;
    }
    catch(std::ios_base::failure& ex) {
        cerr<<ex.what()<<endl;
    }
    savedFile.close();

}

void Board::ReadFromFileLastTurn(const string &filename) {
    ifstream infile(filename,  std::ios::in);
    if (!infile.is_open()) { cerr<< "Σφάλμα κατά την διάρκεια του ανοίγματος του αρχείου!"<<endl; return; }
    try {
         string name ;
         infile.read(reinterpret_cast<char*>(&name), name.size());
         this->changeLastTurn(name);
    }
    catch(std::ios_base::failure& ex) {
        cerr<<ex.what()<<endl;
    }
    infile.close();
}

void Board::changeLastTurn(const string &name) {

    if(name == "white"){
        this->colorOfCurrentPlayer = Color::WHITE;
    }else{
        this->colorOfCurrentPlayer = Color::BLACK;
    }

}


Board::~Board() = default;

