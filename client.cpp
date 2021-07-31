#include "iostream"
#include "clientClass.h"
#include "clientClass.h"

using namespace std;

int main(){
    clientClass c("127.0.0.1", 8080);
    if (c.connect()){
        c.run_game();
    }

    return 0;
}