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
    Button new_game(600, 310, 200, 40,
                    "../assets/button_new-game.png", "../assets/button_new-game1.png",
                    [&main_window]() {
                        SDL_MessageBoxData data;
                        data.title = "New Game";
                        data.flags = 0;
                        data.message = "Are you sure?";
                        data.numbuttons = 2;
                        data.window = main_window->getWindow();
                        SDL_MessageBoxButtonData button[2];
                        button[0].flags = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT;
                        button[0].buttonid = 0;
                        button[0].text = "Yes";
                        button[1].flags = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT;
                        button[1].buttonid = 1;
                        button[1].text = "No";
                        data.buttons = button;
                        int buttonid;
                        if( SDL_ShowMessageBox(&data, &buttonid) < 0 ) {
                            // error occurred
                        } else if( buttonid == 0 ) {
                            // user clicked yes
                        } else if( buttonid == 1 ) {
                            // user clicked no
                        }
                    });
    Button cancel_move(600, 351, 200, 40,
                    "../assets/button_cancel-move.png", "../assets/button_cancel-move1.png",
                    [&x]() {
                    });


    BoardWidget board(10,10,590);
    ScrollableWidget histo_test(600,10,200, 300, "../assets/scr_background.png", 10);
    SDL_Texture * bg = main_window->loadImg((string) "../assets/background.png");

    while(continueGame) {
        SDL_RenderClear(main_window->getRender());
        SDL_RenderCopy(main_window->getRender(), bg, nullptr, nullptr);
        new_game.print();
        cancel_move.print();
        histo_test.print();
        board.print();

        SDL_RenderPresent(main_window->getRender());

        eventHandler->handle(event, continueGame);
    }



    return 0;
}

