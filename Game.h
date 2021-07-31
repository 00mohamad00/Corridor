//
// Created by Mohammad Ebrahimi on 7/22/21.
//

#ifndef CORRIDORIII_GAME_H
#define CORRIDORIII_GAME_H

#define STATUS_INITIALIZING 1
#define STATUS_PLAYING 1

#include "Board.h"
#include "Pawn.h"
#include "iostream"

using namespace std;

class Game {
public:
    Game(int n = 11);
    ~Game();

    void run();
    int add_new_player();
//    void remove_player(int id);

    void move(int id, int dir);
    void create_wall(int x, int y, int dir);

    int get_turn();
    int get_status();
    json get_map();
private:
    Board* board;
    std::vector<Pawn*> pawns;
    int turn;
    int status;
    int winner_id;

    Pawn* find_by_id(int id);

    bool is_finished();

    void next_turn();
};


#endif //CORRIDORIII_GAME_H
