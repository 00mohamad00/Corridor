//
// Created by Mohammad Ebrahimi on 7/22/21.
//

#include <sstream>
#include "Game.h"
#include "errors.h"
#include "string"

Game::Game(int n) {
    board = new Board(n);
    turn = 0;
    winner_id = -1;
    status = STATUS_INITIALIZING;
}

Game::~Game() {
    delete board;
    for (auto pawn:pawns){
        delete pawn;
    }
}

void Game::run() {
    while (!is_finished()){
        board->print();
        string line;
        getline(cin, line);
        stringstream ss(line);

        string request;
        int player_id;
        ss >> request >> player_id;

        if (player_id!=turn){
            cout << "[wrong turn]: it's player " << turn << " turn" << endl;
            continue;
        }

        if (request=="move"){
            int dir;
            ss >> dir;

            try {
                move(player_id, dir);
            }
            catch (position_error& e){
                cout << e.what() << endl;
                cout << "try again" << endl;
                continue;
            }

        } else if (request=="create_wall"){
            int x, y, dir;
            ss >> x >> y >> dir;
            try {
                create_wall(x, y, dir);
            }
            catch (position_error& e){
                cout << e.what() << endl;
                cout << "try again" << endl;
                continue;
            }
        }
        else{
            continue;
        }
        next_turn();
    }
    board->print();
    cout << winner_id << " is the winner !!!" << endl;
}

int Game::add_new_player() {
    if (status != STATUS_INITIALIZING){
        throw server_status_error("server isn't in initializing mode");
    }
    Pawn* pawn = new Pawn(board);
    pawns.push_back(pawn);
    if (pawns.size() == 4)
        start();
    return pawn->get_id();
}

void Game::move(int id, int dir) {
    Pawn* pawn = find_by_id(id);
    pawn->move_by_dir(dir);
}

Pawn *Game::find_by_id(int id) {
    for (auto& pawn:pawns){
        if (id==pawn->get_id())
            return pawn;
    }
    throw wrong_id_error("wrong player id");
}

bool Game::is_finished() {
    for (int i = 0; i < pawns.size(); ++i) {
        if (pawns[i]->is_game_finished()){
            winner_id = i;
            return true;
        }
    }
    return false;
}

void Game::next_turn() {
    turn += 1;
    turn %= pawns.size();
}

void Game::create_wall(int x, int y, int dir) {
    if (dir==1){
        board->create_wall_up_down(x, y-1, y+1);
    } else{
        board->create_wall_left_right(y, x-1, x+1);
    }
}

//void Game::remove_player(int id) {
//    Pawn* pawn;
//    for (int i = 0; i < pawns.size(); ++i) {
//        if (pawns[i]->get_id() == id){
//            pawn = pawns[id];
//
//            break;
//        }
//    }
//    delete pawn;
//}


int Game::get_turn() {
    return turn;
}

json Game::get_map() {
    return board->get_as_json();
}

int Game::get_status() {
    return status;
}

void Game::check_finish() {
    if (is_finished())
        status = STATUS_FINISHED;
}

int Game::get_winner() {
    return winner_id;
}

void Game::start() {
    status = STATUS_PLAYING;
}

int Game::number_of_players() {
    return pawns.size();
}
