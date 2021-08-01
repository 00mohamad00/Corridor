//
// Created by Mohammad Ebrahimi on 7/31/21.
//

#ifndef CORRIDOR_CLIENTCLASS_H
#define CORRIDOR_CLIENTCLASS_H

#define STATUS_INITIALIZING 1
#define STATUS_PLAYING 2
#define STATUS_FINISHED 3

#include "httplib.h"
#include "errors.h"
#include "json.hpp"
#include "string"
#include "Board.h"

class clientClass {
public:
    clientClass(std::string server_addr, int server_port);
    ~clientClass();

    bool connect();
    void run_game();
    void get_data();
    void print();
    void start();
    void move(int dir);
    void create_wall(int x, int y, int dir);
    void get_request_from_user();
private:
    std::vector<Pawn*> pawns;
    httplib::Client *cli;
    Board* board;
    int id;
    int turn, pre_turn;
    int status;
    int winner_id;
    int number_of_clients;
};


#endif //CORRIDOR_CLIENTCLASS_H
