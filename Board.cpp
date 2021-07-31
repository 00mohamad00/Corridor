//
// Created by Mohammad Ebrahimi on 7/22/21.
//

#include "Board.h"
#include "iostream"

Board::Board(int n) {
    map = std::vector<std::vector<Pawn*> >(n, std::vector<Pawn*>(n, nullptr));
}

Board::~Board() {

}

void Board::print() {
    int len = map.size();
    for (int i = 0; i < len; ++i) {
        std::cout << "-------------------------------------" << std::endl;
        for (int j = 0; j < len; ++j) {
            std::cout << "|" << ((map[i][j] == nullptr)? "  ": " "+std::to_string(map[i][j]->get_id()))+" ";
        } std::cout << "|" << std::endl;
    } std::cout << "-------------------------------------" << std::endl;
}

bool Board::is_correct_pos(int x, int y) {
    return x>=0 && x<map.size() && y>=0 && y<map.size();
}

bool Board::is_available(int x, int y) {
    return map[x][y] == nullptr;
}

void Board::set_pos(Pawn *pawn, int x, int y) {
    if (!is_correct_pos(x, y) || !is_available(x, y)){
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



