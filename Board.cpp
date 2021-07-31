//
// Created by Mohammad Ebrahimi on 7/22/21.
//

#include "Board.h"
#include "iostream"

Board::Board(int n) {
    map = std::vector<std::vector<Pawn*> >(n, std::vector<Pawn*>(n, nullptr));
    wall = new Pawn();
}

Board::~Board() {
    delete wall;
}

void Board::print() {
    int len = map.size();
    for (int i = 0; i < len; ++i) {
        std::cout << "---------------------------------------------" << std::endl;
        for (int j = 0; j < len; ++j) {
            if (map[i][j] == nullptr)
                std::cout << "|   ";
            else if (map[i][j]->get_id()==-1)
                std::cout << "| # ";
            else
                std::cout << "| "+ std::to_string(map[i][j]->get_id()) + " ";
        } std::cout << "|" << std::endl;
    }   std::cout << "---------------------------------------------" << std::endl;
}

bool Board::is_correct_pos(int x, int y) {
    return x>=0 && x<map.size() && y>=0 && y<map.size();
}

bool Board::is_available(int x, int y) {
    return map[x][y] == nullptr;
}

void Board::set_pos(Pawn *pawn, int x, int y) {
    if (!is_accessible(x, y)){
        throw position_error("wrong position");
    }
    remove_pos(pawn);
    map[x][y] = pawn;
}

void Board::remove_pos(Pawn* pawn) {
    for(auto& l:map){
        for (auto& cell:l) {
            if (cell == pawn){
                cell = nullptr;
                return;
            }
        }
    }
    // TODO: error
}

void Board::create_solo_wall(int x, int y) {
    if (!is_accessible(x, y)){
        throw position_error("wrong position");
    }
    map[x][y] = wall;
}

bool Board::is_accessible(int x, int y) {
    return is_correct_pos(x, y) && is_available(x, y);
}

void Board::create_wall_up_down(int x, int up_y, int down_y) {
    for (int i = up_y; i <= down_y; ++i) {
        if (!is_accessible(x, i))
            throw position_error("wrong position for wall");
    }
    for (int i = up_y; i <= down_y; ++i) {
        create_solo_wall(x, i);
    }
}

void Board::create_wall_left_right(int y, int left_x, int right_x) {
    for (int i = left_x; i <= right_x; ++i) {
        if (!is_accessible(i, y))
            throw position_error("wrong position for wall");
    }
    for (int i = left_x; i <= right_x; ++i) {
        create_solo_wall(i ,y);
    }
}



