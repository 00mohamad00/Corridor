//
// Created by Mohammad Ebrahimi on 7/22/21.
//

#include "Pawn.h"

int initial_pos_x[4] = {0, 10, 10, 0};
int initial_pos_y[4] = {0, 10, 0, 10};

int Pawn::static_id = 0;

Pawn::Pawn(Board* _board) {
    if (static_id >= 4){
        throw max_player("maximum player");
    }
    id = static_id;
    color = static_cast<Color>(static_id);
    board = _board;

    x = init_x = initial_pos_x[id];
    y = init_y = initial_pos_y[id];
    set_pos(x, y);

    static_id++;
}

Pawn::Pawn() {
    id = -1;
}

Pawn::~Pawn() {
    static_id--;
    board->remove_pos(this);
}

int Pawn::get_id() {
    return id;
}

void Pawn::set_pos(int _x, int _y) {
    board->set_pos(this, _x, _y);
    x = _x;
    y = _y;
}

void Pawn::move_by_dir(int dir) {
    if (dir == UP){
        set_pos(x-1, y);
    } else if (dir == DOWN){
        set_pos(x+1, y);
    } else if (dir == RIGHT){
        set_pos(x, y+1);
    } else if (dir == LEFT){
        set_pos(x, y-1);
    }
}

bool Pawn::is_game_finished() {
    if (x==5 && y==5)
        return true;
    return false;
}
