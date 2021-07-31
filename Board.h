//
// Created by Mohammad Ebrahimi on 7/22/21.
//

#ifndef CORRIDORIII_BOARD_H
#define CORRIDORIII_BOARD_H

#include "vector"
#include "Pawn.h"
#include "errors.h"

class Pawn;

class Board {
public:
    Board(int n);
    ~Board();

    void print();

    bool is_correct_pos(int x, int y);
    bool is_available(int x, int y);

private:
    void set_pos(Pawn *pawn, int x, int y);
    void remove_pos(Pawn* pawn);
     std::vector<std::vector<Pawn*> >map;

     friend class Pawn;
};


#endif //CORRIDORIII_BOARD_H
