#include "httplib.h"
#include "iostream"
#include "json.hpp"

using namespace std;
using namespace nlohmann;

int main(){
    httplib::Server server;
    server.Get("/new_client", [](const httplib::Request &req, httplib::Response &res) {
            json j;
            j["id"] = 1;
            j["status"] = "ok"; // j["status"] = "no_new_client";
            res.set_content(j.dump(), "application/json");
        }
    );

    cout << "[Starting Server]: 127.0.0.1:8080" << endl;
    server.listen("127.0.0.1", 8080);
    cout << "[Finished]" << endl;

    return 0;
}
