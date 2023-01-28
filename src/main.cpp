#include <iostream>
#include <SDL2/SDL.h>
#include "Window/EventHandler.h"
#include "Window/Window.h"
#include "Window/Button.h"
#include "Window/BoardWidget.h"
#include "Window/ScrollableWidget.h"
#include <fstream>


using namespace std;

int main(int argc, char** argv) {
// returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    Window* main_window = Window::getMainWindow();
    EventHandler *eventHandler = EventHandler::getEventHandler();

    bool continueGame = true;
    SDL_Event event;
    int x = 0;
    Button new_game(600, 300, 200, 50,
                    "../assets/btn_nouv_jeu_1.png", "../assets/btn_nouv_jeu_2.png",
                    [&x]() {
                        SDL_ShowSimpleMessageBox(0, "Test", "Bonjour le monde", Window::getMainWindow()->getWindow());
                    });


    BoardWidget board(0,0,600);
    ScrollableWidget histo_test(600,0,200, 300, "../assets/scr_background.png", 10);
    SDL_Texture * bg = main_window->loadPng((string) "../assets/background.png");

    while(continueGame) {
        SDL_RenderClear(main_window->getRender());
        SDL_RenderCopy(main_window->getRender(), bg, nullptr, nullptr);
        new_game.print();
        histo_test.print();
        board.print();

        SDL_RenderPresent(main_window->getRender());

        eventHandler->handle(event, continueGame);
    }



    return 0;
}

