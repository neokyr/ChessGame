cmake_minimum_required(VERSION 3.18)
PROJECT(chess)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "64-bit architecture detected")
    SET(SDL2_custom_path ${CMAKE_SOURCE_DIR}/SDL2-2.26.2/x86_64-w64-mingw32)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(STATUS "32-bit architecture detected")
    SET(SDL2_custom_path ${CMAKE_SOURCE_DIR}/SDL2-2.26.2/i686-w64-mingw32)
endif () #Architecture check

add_executable(chess
        src/main.cpp
        src/Window/Button.cpp
        src/Window/Widget.cpp
        src/Window/Window.cpp
        src/Window/EventHandler.cpp
        src/Window/BoardWidget.cpp
        src/Window/ScrollableWidget.cpp
        src/Board.cpp
        src/Piece.cpp
        src/Historic.cpp
        include/Window/EventHandler.h
        include/Window/Button.h
        include/Window/Widget.h
        include/Window/Window.h
        include/Window/BoardWidget.h
        include/Window/ScrollableWidget.h
        include/Window/HistoricWidget.h
        include/Board.h
        include/Piece.h
        include/Game.h
        include/Player.h
        include/Historic.h
        src/Game.cpp)


SET(SDL2_PATH ${SDL2_custom_path})
SET(SDL2_image_PATH ${SDL2_custom_path})
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${SDL2_custom_path}/lib/cmake/SDL2_image)

find_package(SDL2 REQUIRED)
find_package(sdl2_image REQUIRED)

include_directories(include/ ${SDL2_INCLUDE_DIR}/.. ${SDL2_custom_path}/include)
target_link_libraries(chess ${SDL2_LIBRARY} ${SDL2_custom_path}/lib/libSDL2_image.dll.a)
file(COPY ${SDL2_custom_path}/bin/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${SDL2_custom_path}/bin/SDL2_image.dll DESTINATION ${CMAKE_BINARY_DIR})
