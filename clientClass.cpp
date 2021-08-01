//
// Created by Mohammad Ebrahimi on 7/31/21.
//

#include "clientClass.h"

using namespace nlohmann;

clientClass::clientClass(std::string server_addr, int server_port = 8080) {
    id = -1;
    cli = new httplib::Client(server_addr, server_port);
    board = new Board(11);
    pre_turn = -1;
    turn = -1;
    for (int i = 0; i < 4; ++i) {
        pawns.push_back(new Pawn(i));
    }
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
    int number_of_players;
    if (id == 0){
        std::cout << "Set number of players, MAX = 4" << std::endl;
        std::cin >> number_of_players;
    }
    get_data();
    while (status != STATUS_FINISHED){
        if (status==STATUS_INITIALIZING){
            system("clear");
            std::cout << "Number of connected clients: " << number_of_clients << std::endl;
            if (id==0 && number_of_players==number_of_clients){
                start();
            }
        } else {
            if (turn!=pre_turn){
                system("clear");
                std::cout << id << std::endl;
                print();
            }
            if (turn==id){
                get_request_from_user();
            }
        }
        usleep(200);
        get_data();
    }
    if (winner_id==id)
        std::cout << "You won the game!!!" << std::endl;
    else
        std::cout << winner_id << " won the game:(" << std::endl;
}

void clientClass::get_data() {
    httplib::Headers headers = {
            { "id", std::to_string(id) }
    };
    auto res = cli->Get("/game_status", headers);
    auto j = json ::parse(res->body);

    status = j["status"].get<int>();
    number_of_clients = j["clients"].get<int>();

    if (status==STATUS_PLAYING){
        pre_turn = turn;
        turn = j["turn"].get<int>();
        board->set_by_json(j["map"], pawns);
    }
    if (status==STATUS_FINISHED){
        winner_id = j["winner"].get<int>();
    }
}

void clientClass::start() {
    auto res = cli->Get("/start");
}


void clientClass::print() {
    board->print();
}

void clientClass::move(int dir) {
    if (turn!=id){
        return;
    }
    httplib::Headers headers = {
            { "id", std::to_string(id) },
            { "dir", std::to_string(dir)  }
    };
    auto res = cli->Get("/move", headers);
    auto j = json ::parse(res->body);
    if (j["status"].get<std::string>() == "0"){
        throw position_error(j["error"].get<std::string>());
    }
}

void clientClass::create_wall(int x, int y, int dir) {
    if (turn!=id){
        return;
    }
    httplib::Headers headers = {
            { "id", std::to_string(id) },
            { "x", std::to_string(x)},
            { "y", std::to_string(y)},
            { "dir", std::to_string(dir)  }
    };
    auto res = cli->Get("/create_wall", headers);
    auto j = json ::parse(res->body);
    if (j["status"].get<std::string>() == "0"){
        throw position_error(j["error"].get<std::string>());
    }
}

void clientClass::get_request_from_user() {
    std::cout << "UP: 0, DOWN: 1, RIGHT: 2, LEFT: 3" << std::endl;
    std::cout << "Y:";
    std::string line;
    getline(std::cin, line);
    std::stringstream ss(line);

    std::string request;

    ss >> request;
    if (request=="move"){
        int dir;
        ss >> dir;
        try {
            move(dir);
        }catch (position_error& e){
            std::cout << "You can't go there" << std::endl;
        }
    }else if (request=="create_wall"){
        int x, y, dir;
        ss >> x >> y >> dir;
        try {
            create_wall(x, y, dir);
        }catch (position_error& e){
            std::cout << "You can't create wall there" << std::endl;
        }
    }else{
        std::cout << "try again" << std::endl;
    }
}



