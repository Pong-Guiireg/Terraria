#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "physics.h"
#include "world.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Rectangle hitbox;
    bool isJumping;
    bool isFalling;
} Player;

void initPlayer(Player *player);
void updatePlayer(Player *player, World *world);
void renderPlayer(Player *player);
void movePlayerLeft(Player *player);
void movePlayerRight(Player *player);
void playerJump(Player *player);
void applyGravity(Player *player);
void updatePlayerPosition(Player *player);
void checkWorldCollisions(Player *player, World *world);

#endif // PLAYER_H
