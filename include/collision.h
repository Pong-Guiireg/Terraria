#ifndef COLLISION_H
#define COLLISION_H

#include <raylib.h>
#include "player.h"

bool check_ground_collision(Rectangle player_rect);
void handle_block_collisions(Player *player);
bool check_collision_with_blocks(Rectangle rect);
void resolve_vertical_collision(Player *player);
void resolve_horizontal_collision(Player *player);

#endif // COLLISION_H
