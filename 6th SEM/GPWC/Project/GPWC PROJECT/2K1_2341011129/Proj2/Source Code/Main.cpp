#include "FlappyBird.h"
#include <ctime>
#include <cstdlib>

int main()
{
    srand(static_cast<unsigned>(time(nullptr)));

    FlappyBird game;
    game.run();

    return 0;
}