#include <iostream>
#include <SDL2/SDL.h>
#include "Window/EventHandler.h"
#include "Window/Window.h"
#include "Window/Button.h"
#include "Window/BoardWidget.h"
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
    Button new_game(400, 200, 100, 40,
                    "../assets/btn_nouv_jeu_1.png", "../assets/btn_nouv_jeu_2.png",
                    [&x]() {
                        x++;
                    });
    Button test(400, 241, 100, 40,
                    "../assets/btn_nouv_jeu_1.png", "../assets/btn_nouv_jeu_2.png",
                    []() {
                        int x;
                        x++;
                    });

    BoardWidget board(0,0,400,400);

    while(continueGame) {
        SDL_RenderClear(main_window->getRender());
        new_game.print();
        test.print();
        board.print();

        SDL_RenderPresent(main_window->getRender());

        eventHandler->handle(event, continueGame);
    }



    return 0;
}

