#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include "player.h"
#include "world.h"
#include "render.h"

typedef struct {
    bool running;
    Player player;
    World world;
} Game;

void initGame(Game *game);
void runGameLoop(Game *game);
void cleanupGame(Game *game);
void updateGame(Game *game);
void handleInput(Game *game);

#endif // GAME_H
