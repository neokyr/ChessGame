
#include "Window/HistoricWidget.h"
#include "Window/Window.h"

HistoricWidget::HistoricWidget(int x, int y, int w, int h, const string &bgPath="", int padding=0) :
    ScrollableWidget(x, y, w, h, bgPath,padding) {

    SDL_Surface *test = Window::loadImgToSurface("../assets/test.png");

    setSurface(test);

}
