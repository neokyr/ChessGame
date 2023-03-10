#pragma once

#include "Board.h"
#include "Piece.h"
#include "vector"
#include "Historic.h"

using namespace std;

class Game {
private:
    Board board_;
    Color current_player_;
    vector<Historic> move_history_;
    void deleteMoveHistory();

public:
    Game();
    ~Game();

    void new_game();
    void cancel_move();
    void change_player();
    bool is_check(Color c);
    bool is_check_mat(Color c);
    bool is_pat(Color c);
    bool can_castling(Color c);
    bool can_big_castling(Color c);
    void saveState(string file_path);
    void loadState(string file_path);

    Board &getBoard();
    Color getCurrentPlayer() const;
    const vector<Historic> &getMoveHistory() const;
    void addHistory(Historic h);
};
