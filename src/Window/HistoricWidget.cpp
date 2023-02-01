
#include "Window/HistoricWidget.h"
#include "Window/Window.h"

HistoricWidget::HistoricWidget(int x, int y, int w, int h, const string &bgPath, int padding, Game& game) :
    ScrollableWidget(x, y, w, h, bgPath,padding), game_(game) {

    SDL_Surface *test = Window::loadImgToSurface("../assets/test.png");

    setSurface(test);

}

void HistoricWidget::print() {



    ScrollableWidget::print();
}
