#ifndef WORLD_H
#define WORLD_H

#include <raylib.h>
#include <math.h>

#define BLOCK_SIZE 32
#define WORLD_WIDTH 1000
#define WORLD_HEIGHT 50

typedef enum {
    BLOCK_AIR,
    BLOCK_DIRT,
    BLOCK_GRASS,
    BLOCK_STONE
} BlockType;

typedef struct World {
    BlockType blocks[WORLD_WIDTH][WORLD_HEIGHT];
} World;

void initWorld(World *world);
void renderWorld(World *world);
bool isBlockSolid(BlockType type);
Rectangle getBlockRect(int x, int y);

#endif // WORLD_H
