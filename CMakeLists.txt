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
    casteling.h casteling.cpp
    null_piece.h null_piece.cpp
    main_state_machine.h main_state_machine.cpp
)
target_link_libraries(chess_console Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS chess_console
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
