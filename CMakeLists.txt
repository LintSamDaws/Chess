cmake_minimum_required(VERSION 3.14)

project(chess_console LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(chess_console

    main.cpp
    board.h board.cpp
    move.h move.cpp
    piece.h piece.cpp
    rook.h rook.cpp
    king.h king.cpp
    bishop.h bishop.cpp
    knight.h knight.cpp
    queen.h queen.cpp
    pawn.h pawn.cpp
    null_piece.h null_piece.cpp
    board_state.h
    state_base.h state_base.cpp
    state_move_check.h state_move_check.cpp
    state_make_move.h state_make_move.cpp
    state_result_check.h state_result_check.cpp
    state_exit.h state_exit.cpp
    notation_reader.h notation_reader.cpp
    game_legend.h game_legend.cpp
    castling.h castling.cpp

)
target_link_libraries(chess_console Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS chess_console
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
