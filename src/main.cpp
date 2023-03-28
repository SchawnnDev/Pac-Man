#include "game/game.h"

using namespace pacman;

int main(int argc, char** argv)
{
    try {
        Game game{};
        game.start();
    } catch(...) {
        return -1;
    }
    return 0;
}
