//
// Created by Mohammad Ebrahimi on 7/22/21.
//

#ifndef CORRIDORIII_GAME_H
#define CORRIDORIII_GAME_H

#define STATUS_INITIALIZING 1
#define STATUS_PLAYING 2
#define STATUS_FINISHED 3

#include "Board.h"
#include "Pawn.h"
#include "iostream"

using namespace std;

class Game {
public:
    Game(int n = 11);
    ~Game();

    void run();
    void start();
    int add_new_player();
//    void remove_player(int id);
    void move(int id, int dir);
    void create_wall(int x, int y, int dir);
    void next_turn();
    int get_turn();
    int get_status();
    int get_winner();
    json get_map();
    void check_finish();
private:
    Board* board;
    std::vector<Pawn*> pawns;
    int turn;
    int status;
    int winner_id;

    Pawn* find_by_id(int id);

    bool is_finished();
};


#endif //CORRIDORIII_GAME_H
