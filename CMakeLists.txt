cmake_minimum_required(VERSION 3.23)
project(chess)

set(CMAKE_CXX_STANDARD 11)


# --- SDL2 SETUP ---
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)
SET(SDL2_PATH ${CMAKE_SOURCE_DIR}/SDL2-2.26.2/x86_64-w64-mingw32)


find_package(SDL2 REQUIRED)

add_executable(chess src/main.cpp include/Board.h include/Piece.h include/Game.h include/Player.h include/Window/EventHandler.h)


include_directories(${SDL2_INCLUDE_DIR}/..)
target_link_libraries(chess ${SDL2_LIBRARY})

