//
// Created by Mohammad Ebrahimi on 7/22/21.
//

#ifndef CORRIDORIII_GAME_H
#define CORRIDORIII_GAME_H

#include "Board.h"
#include "Pawn.h"
#include "iostream"

using namespace std;

class Game {
public:
    Game(int n = 9);
    ~Game();

    void run();
    void add_new_player();
//    void remove_player(int id);
//
    void move(int id, int dir);
//    void create_wall();
private:
    Board* board;
    std::vector<Pawn*> pawns;
    int turn;
    int winner_id;

    Pawn* find_by_id(int id);

    bool is_finished();

    void next_turn();
};


#endif //CORRIDORIII_GAME_H
