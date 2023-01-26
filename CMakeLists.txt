cmake_minimum_required(VERSION 3.22)
project(chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(chess src/main.cpp include/Plateau.h include/Piece.h)

# --- SDL2 SETUP ---
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)
set(SDL2_PATH ${PROJECT_SOURCE_DIR}/SDL2/x86_64-w64-mingw32)

find_package(SDL2 REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/SDL2-2.26.2/x86_64-w64-mingw32/include)
target_link_libraries(chess ${SDL2_LIBRARY})

