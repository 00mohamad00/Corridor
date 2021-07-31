//
// Created by Mohammad Ebrahimi on 7/31/21.
//

#ifndef CORRIDORIII_ERRORS_H
#define CORRIDORIII_ERRORS_H

#include "iostream"

class error{
public:
    error(std::string m){
        message = m;
    }
    std::string what(){
        return message;
    }
private:
    std::string message;
};

class position_error: public error{
    using error::error;
};
class wrong_id_error: public error{
    using error::error;
};
class max_player: public error{
    using error::error;
};

#endif //CORRIDORIII_ERRORS_H
