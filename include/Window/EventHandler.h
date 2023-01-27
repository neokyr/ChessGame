//
// Created by p00ri on 26/01/2023.
//
#pragma once
#include <SDL2/SDL.h>
#include <vector>

using namespace std;

class Event {
public:
    virtual void handleEvent(SDL_Event& e) = 0;
};


class EventHandler {
private:
    vector<Event*> subscribedEvents_;
    EventHandler() = default;
public:
    EventHandler(EventHandler& handler)= delete;
    EventHandler& operator=(EventHandler const& ev) = delete;

    static EventHandler* getEventHandler() {
        static EventHandler handler;

        return &handler;
    }

    void handle(SDL_Event &e, bool &gameRunning);

    void subscribe(Event *event);


};
