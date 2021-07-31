//
// Created by Mohammad Ebrahimi on 7/22/21.
//

#ifndef CORRIDORIII_BOARD_H
#define CORRIDORIII_BOARD_H

#include "vector"
#include "Pawn.h"
#include "errors.h"
#include "json.hpp"

using namespace nlohmann;

class Pawn;

class Board {
public:
    Board(int n);
    ~Board();

    void print();

    bool is_correct_pos(int x, int y);
    bool is_available(int x, int y);
    bool is_accessible(int x, int y);
    void create_solo_wall(int x, int y);
    void create_wall_up_down(int x, int up_y, int down_y);
    void create_wall_left_right(int y, int left_x, int right_x);
    json get_as_json();
private:
    void set_pos(Pawn *pawn, int x, int y);
    void remove_pos(Pawn* pawn);
    std::vector<std::vector<Pawn*> >map;
    Pawn *wall;
    friend class Pawn;
};


#endif //CORRIDORIII_BOARD_H
