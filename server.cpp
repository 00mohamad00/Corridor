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

    server.Get("/start", [&] (const httplib::Request &req, httplib::Response &res) {
           log("Start");
           game.start();
           json j;
           j["status"] = "ok";
           res.set_content(j.dump(), "application/json");
        }
    );

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
            } else if (game.get_status() == STATUS_PLAYING){
                j["map"] = game.get_map();
                j["status"] = game.get_status();
                j["turn"] = game.get_turn();
            } else{
                j["winner"] = game.get_winner();
            };
            res.set_content(j.dump(), "application/json");
        }
    );

    server.Get("/create_wall", [&](const httplib::Request &req, httplib::Response &res) {
            int player_id = std::stoi(req.get_header_value("id"));
            int x = std::stoi(req.get_header_value("x"));
            int y = std::stoi(req.get_header_value("y"));
            int dir = std::stoi(req.get_header_value("dir"));
            log("Create Wall");

            json j;

            if (player_id!=game.get_turn()){
                log("ERROR", "Wrong Turn");
                j["status"] = "0";
                j["error"] = "turn";
                res.set_content(j.dump(), "application/json");
                return;
            }

            try {
                game.create_wall(x, y, dir);
                j["status"] = "1";
                game.next_turn();
                game.check_finish();
            }
            catch (position_error& e){
                log("ERROR", "Position");
                j["status"] = "0";
                j["error"] = "position";
            }
            res.set_content(j.dump(), "application/json");
        }
    );

    server.Get("/move", [&](const httplib::Request &req, httplib::Response &res) {
           int player_id = std::stoi(req.get_header_value("id"));
           int dir = std::stoi(req.get_header_value("dir"));
           log("Move", "player id = " + std::to_string(player_id));

           json j;

           if (player_id!=game.get_turn()){
               log("ERROR", "Wrong Turn");
               j["status"] = "0";
               j["error"] = "turn";
               res.set_content(j.dump(), "application/json");
               return;
           }

           try {
               game.move(player_id, dir);
               j["status"] = "1";
               game.next_turn();
               game.check_finish();
           }
           catch (position_error& e){
               log("ERROR", "Position");
               j["status"] = "0";
               j["error"] = "position";
           }
           res.set_content(j.dump(), "application/json");
        }
    );


    log("Starting Server", "127.0.0.1:8080");
    server.listen("127.0.0.1", 8080);
    log("Finishing");

    return 0;
}
