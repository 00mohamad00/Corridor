//
// Created by Mohammad Ebrahimi on 7/22/21.
//

#ifndef CORRIDORIII_PAWN_H
#define CORRIDORIII_PAWN_H

#include "Board.h"
#include "errors.h"

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

enum Color{Red, Blue, Green, Yellow};

class Board; // TODO: ???

class Pawn {
public:
    Pawn(Board* _board);
    Pawn(int id);
    Pawn();
    ~Pawn();

    int get_id();
    void set_pos(int _x, int _y);
    void move_by_dir(int dir);
    bool is_game_finished();
private:
    static int static_id;
    int id;
    int init_x, init_y;
    int x, y;
    Color color;

    Board* board;
};


#endif //CORRIDORIII_PAWN_H
