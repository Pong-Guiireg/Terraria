#include "../include/game.h"

int main(void)
{
    Game game;

    initGame(&game);
    runGameLoop(&game);
    cleanupGame(&game);

    return 0;
}
