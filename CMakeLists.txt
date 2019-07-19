cmake_minimum_required(VERSION 3.10)
project(untitled23)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(include/errors)
include_directories(logger)

add_executable(untitled23
        include/errors/ErrorCode.h
        include/Bishop.h
        include/Board.h
        include/Color.h
        include/Game.h
        include/King.h
        include/Knight.h
        include/Pawn.h
        include/Piece.h
        include/Queen.h
        include/Rook.h
        include/Tile.h
        include/utils.h
        logger/Logger.cpp
        logger/Logger.h
        Bishop.cpp
        Board.cpp
        Game.cpp
        King.cpp
        Knight.cpp
        main.cpp
        Pawn.cpp
        Piece.cpp
        Queen.cpp
        Rook.cpp
        Tile.cpp
        Utils.cpp)
