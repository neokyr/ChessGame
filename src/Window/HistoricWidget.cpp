
#include <stdexcept>
#include "Window/HistoricWidget.h"
#include "Window/Window.h"

HistoricWidget::HistoricWidget(int x, int y, int w, int h, const string &bgPath, int padding, Game& game) :
    ScrollableWidget(x, y, w, h, bgPath,padding), game_(game) {


}

void HistoricWidget::print() {
    vector<Historic> moveHistory = game_.getMoveHistory();
    Window* win = Window::getMainWindow();
    int h = 30 * (int) moveHistory.size() + 10;
    int h2 = getPosition()->h;

    SDL_Texture *combinedTexture = SDL_CreateTexture(win->getRender(),
                                                     SDL_PIXELFORMAT_ABGR8888,
                                                     SDL_TEXTUREACCESS_TARGET,
                                                     getPosition()->w - getPadding() *2,
                                                     h < h2 ? h2 : h);
    if(combinedTexture == nullptr) throw runtime_error(SDL_GetError());

    SDL_SetTextureBlendMode(combinedTexture, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(win->getRender(), combinedTexture);
    SDL_SetRenderDrawColor(win->getRender(), 0,0,0,0);
    SDL_RenderClear(win->getRender());
    for (int i = 0; i < moveHistory.size(); ++i) {
        Piece* moving = moveHistory[i].getMoving();
        Piece* destroyed = moveHistory[i].getDestroyed();

        int line =(int) (moveHistory.size() - i -1) *30 + 5;
        SDL_Rect o1 = { 5,line , 25,25};
        SDL_Rect o1x = { 26, line, 20,25};
        SDL_Rect o1y = { 46, line, 20,25};
        SDL_Rect o2x = { 71, line, 20,25};
        SDL_Rect o2y = { 91, line, 20,25};
        SDL_Rect d = { 112, line, 25,25};
        if(moving->getColor() == WHITE) {
            SDL_RenderCopy(win->getRender(), win->getWhitePieces()[moving->get_type()], nullptr, &o1);
        } else {
            SDL_RenderCopy(win->getRender(), win->getBlackPieces()[moving->get_type()], nullptr, &o1);
        }
        SDL_RenderCopy(win->getRender(),win->getNumbers()[moveHistory[i].getFrom().first], nullptr, &o1x);
        SDL_RenderCopy(win->getRender(),win->getLetters()[moveHistory[i].getFrom().second], nullptr, &o1y);
        SDL_RenderCopy(win->getRender(),win->getNumbers()[moveHistory[i].getTo().first], nullptr, &o2x);
        SDL_RenderCopy(win->getRender(),win->getLetters()[moveHistory[i].getTo().second], nullptr, &o2y);

        if(destroyed != nullptr) {
            if(destroyed->getColor() == WHITE) {
                SDL_RenderCopy(win->getRender(), win->getWhitePieces()[destroyed->get_type()], nullptr, &d);
            } else {
                SDL_RenderCopy(win->getRender(), win->getBlackPieces()[destroyed->get_type()], nullptr, &d);
            }
        }
    }

    SDL_SetRenderTarget(win->getRender(), nullptr);

    setRenderTexture(combinedTexture);

    ScrollableWidget::print();
}
