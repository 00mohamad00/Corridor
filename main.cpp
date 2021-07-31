#include <iostream>
#include "Game.h"

int main() {
    Game game(11);
    game.add_new_player();
    game.add_new_player();
    game.add_new_player();
    game.run();
    return 0;
}
