#include "Game.h"
#include <ctime>
#include <cstdlib>

int main(){
    srand(static_cast<unsigned>(time(nullptr)));

    Game game;
    game.run();

    return 0;
}