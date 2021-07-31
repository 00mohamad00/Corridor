#include "httplib.h"
#include "iostream"
#include "json.hpp"
#include "Game.h"

using namespace std;
using namespace nlohmann;

void log(string title, string text=""){
    cerr << "[" << title << "] " << text << endl;
}

int main(){
    Game game;
    httplib::Server server;

    server.Get("/new_client", [&] (const httplib::Request &req, httplib::Response &res) {
            log("GET", "new_client");
            json j;
            try {
                j["id"] = game.add_new_player();
                j["status"] = "ok"; // j["status"] = "no_new_client";
            }catch (max_player_error& e){
                j["id"] = -1;
                j["status"] = e.what();
                log("ERROR", e.what());
            }
            catch (server_status_error& e){
                j["id"] = -1;
                j["status"] = e.what();
                log("ERROR", e.what());
            }
            res.set_content(j.dump(), "application/json");
        }
    );

    server.Get("/game_status", [&](const httplib::Request &req, httplib::Response &res) {
            json j;
            log("GET", "status");
            if (game.get_status() == STATUS_INITIALIZING){
                j["status"] = STATUS_INITIALIZING;
            } else{
                j["map"] = game.get_map();
                j["status"] = game.get_status();
                j["turn"] = game.get_turn();
            }
            res.set_content(j.dump(), "application/json");
        }
    );

    server.Get("/create_wall", [&](const httplib::Request &req, httplib::Response &res) {
            int player_id = req.get_header_value<int>("id");
            int x = req.get_header_value<int>("x");
            int y = req.get_header_value<int>("y");
            int dir = req.get_header_value<int>("dir");
            log("Create Wall");

            if (player_id!=game.get_turn()){
                log("ERROR", "Wrong Turn");
                res.status = 500;
                return;
            }
            try {
                game.create_wall(x, y, dir);
                res.status = 200;
                return;
            }
            catch (position_error& e){
                log("ERROR", "Position");
                res.status = 500;
                return;
            }
        }
    );


    log("Starting Server", "127.0.0.1:8080");
    server.listen("127.0.0.1", 8080);
    log("Finishing");

    return 0;
}
