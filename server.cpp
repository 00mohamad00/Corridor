#include "httplib.h"
#include "iostream"
#include "vector"

using namespace std;

int main(){
    httplib::Server server;
    server.Get("/admin", [](const httplib::Request &req, httplib::Response &res) {
            auto id = req.get_header_value("id");
            res.set_content(id, "text/plain");
        }
    );

    cout << "[Starting Server]: 127.0.0.1:8080" << endl;
    server.listen("127.0.0.1", 8080);
    cout << "[Finished]" << endl;

    return 0;
}
