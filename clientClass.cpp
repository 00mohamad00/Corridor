//
// Created by Mohammad Ebrahimi on 7/31/21.
//

#include "clientClass.h"

using namespace nlohmann;

clientClass::clientClass(std::string server_addr, int server_port = 8080) {
    id = -1;
    cli = new httplib::Client(server_addr, server_port);
    board = new Board(11);
}

clientClass::~clientClass() {
    delete cli;
}

bool clientClass::connect() {
    httplib::Headers headers = {
            { "id", std::to_string(id) }
    };
    auto res = cli->Get("/new_client", headers);
    auto j = json ::parse(res->body);

    if (j["status"].get<std::string>() == "ok"){
        id = j["id"].get<int>();
        return 1;
    }
    else{
        std::cout << "server is full, try again later" << std::endl;
        return 0;
    }
}

void clientClass::run_game() {
//    while (!game_is_over()){
//        get_data();
//        if (status==mine){
//            get_data_from_user();
//        }
//        wait(100ms);
//    }
}
