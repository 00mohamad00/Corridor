#include "httplib.h"
#include "iostream"

using namespace std;

int main(){
    httplib::Headers headers = {
            { "id", to_string(-1) }
    };
    httplib::Client cli("127.0.0.1", 8080);
    auto res = cli.Get("/admin", headers);

    cout << res->status << endl;
    cout << res->body << endl;
}