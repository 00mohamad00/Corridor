//
// Created by Mohammad Ebrahimi on 7/31/21.
//

#ifndef CORRIDOR_CLIENTCLASS_H
#define CORRIDOR_CLIENTCLASS_H

#include "httplib.h"
#include "json.hpp"
#include "string"
#include "Board.h"

class clientClass {
public:
    clientClass(std::string server_addr, int server_port);
    ~clientClass();

    bool connect();
    void run_game();
//    void get_data();
private:
    httplib::Client *cli;
    Board* board;
    int id;
};


#endif //CORRIDOR_CLIENTCLASS_H
