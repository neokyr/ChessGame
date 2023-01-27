//
// Created by p00ri on 26/01/2023.
//
#include "../../include/Window/EventHandler.h"

void EventHandler::handle(SDL_Event &e, bool &gameRunning) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            gameRunning = false;
        }

        for (auto event: subscribedEvents_) {
            event->handleEvent(e);
        }
    }

}

void EventHandler::subscribe(Event *event) {
    subscribedEvents_.push_back(event);
}
