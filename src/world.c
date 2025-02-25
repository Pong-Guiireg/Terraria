#include "../include/world.h"
#include "../include/math_utils.h"  // Pour utiliser clamp()
#include <stdlib.h>                  // Pour utiliser rand()
#include <time.h>

/**
 * Initialize the game world with terrain generation
 * Creates a large world with varied terrain using different sine frequencies
 * and adds some platform structures throughout the world
 */
void initWorld(World *world)
{
    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Initialiser tous les blocs à l'air
    for (int x = 0; x < WORLD_WIDTH; x++)
    {
        for (int y = 0; y < WORLD_HEIGHT; y++)
        {
            world->blocks[x][y] = BLOCK_AIR;
        }
    }

    // Générer la ligne de base du terrain
    int baseHeights[WORLD_WIDTH];

    // Générer un terrain continu avec plusieurs fréquences
    for (int x = 0; x < WORLD_WIDTH; x++)
    {
        // Utiliser plusieurs fréquences pour créer un terrain plus varié
        float highFreq = sin(x * 0.05f) * 3.0f;
        float medFreq = sin(x * 0.02f) * 7.0f;
        float lowFreq = sin(x * 0.005f) * 15.0f;

        // Combinaison des fréquences pour un terrain plus naturel
        int groundHeight = 30 + (int)(highFreq + medFreq + lowFreq);

        // Limiter la hauteur pour éviter de déborder
        groundHeight = clamp(groundHeight, 10, WORLD_HEIGHT - 5);

        // Stocker la hauteur pour référence ultérieure
        baseHeights[x] = groundHeight;

        // Créer les différentes couches
        for (int y = groundHeight; y < WORLD_HEIGHT; y++)
        {
            if (y == groundHeight)
                world->blocks[x][y] = BLOCK_GRASS;
            else if (y < groundHeight + 5)
                world->blocks[x][y] = BLOCK_DIRT;
            else
                world->blocks[x][y] = BLOCK_STONE;
        }
    }

    // Ajouter des plateformes dans un second passage
    // Uniquement aux endroits appropriés pour éviter les plateformes flottantes
    for (int x = 0; x < WORLD_WIDTH; x += 25 + rand() % 25)  // Répartition plus aléatoire
    {
        // Ne générer une plateforme que si c'est près d'une colline ou d'une montagne
        if (x > 5 && x < WORLD_WIDTH - 15)
        {
            // Calculer la hauteur moyenne autour de ce point
            int avgHeight = 0;
            for (int i = x - 5; i < x + 5; i++) {
                avgHeight += baseHeights[i];
            }
            avgHeight /= 10;

            // Trouver le point le plus haut à proximité
            int highestPoint = baseHeights[x];
            for (int i = x - 5; i < x + 5; i++) {
                if (baseHeights[i] < highestPoint) {
                    highestPoint = baseHeights[i];
                }
            }

            // Ne créer une plateforme que si nous sommes dans une zone appropriée
            if (baseHeights[x] <= avgHeight + 3)
            {
                // Platforme à quelques blocs au-dessus du point le plus haut
                int platformHeight = highestPoint - (3 + rand() % 4);

                // Vérifier que la plateforme n'est pas trop haute par rapport au sol
                if (platformHeight < baseHeights[x] - 15) {
                    platformHeight = baseHeights[x] - (5 + rand() % 5);
                }

                // Garantir une hauteur minimale et maximale
                platformHeight = clamp(platformHeight, 5, WORLD_HEIGHT - 10);

                // Créer une plateforme de taille variable
                int platformWidth = 3 + rand() % 8;

                // Éviter de sortir des limites
                if (x + platformWidth >= WORLD_WIDTH) {
                    platformWidth = WORLD_WIDTH - x - 1;
                }

                // Générer la plateforme uniquement si elle n'est pas trop élevée ou directement au-dessus du sol
                if (platformWidth > 0 && platformHeight > baseHeights[x] + 4) {
                    for (int px = 0; px < platformWidth; px++) {
                        world->blocks[x + px][platformHeight] = BLOCK_GRASS;

                        // Support sous la plateforme (comme un petit îlot)
                        for (int py = 1; py < 2 + rand() % 2; py++) {
                            if (platformHeight + py < WORLD_HEIGHT) {
                                world->blocks[x + px][platformHeight + py] = BLOCK_DIRT;
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * Render the visible portion of the world
 * Draws each block with its corresponding color
 */
void renderWorld(World *world)
{
    int startX = 0;
    int startY = 0;
    int endX = WORLD_WIDTH;
    int endY = WORLD_HEIGHT;

    // Seulement rendre les blocs visibles
    startX = fmax(0, startX);
    startY = fmax(0, startY);
    endX = fmin(WORLD_WIDTH, endX);
    endY = fmin(WORLD_HEIGHT, endY);

    for (int x = startX; x < endX; x++)
    {
        for (int y = startY; y < endY; y++)
        {
            BlockType block = world->blocks[x][y];

            if (block != BLOCK_AIR)
            {
                Color blockColor;

                switch (block)
                {
                    case BLOCK_GRASS:
                        blockColor = GREEN;
                        break;
                    case BLOCK_DIRT:
                        blockColor = BROWN;
                        break;
                    case BLOCK_STONE:
                        blockColor = GRAY;
                        break;
                    default:
                        blockColor = WHITE;
                }

                Rectangle blockRect = getBlockRect(x, y);
                DrawRectangleRec(blockRect, blockColor);
            }
        }
    }
}

/**
 * Check if a block type is solid (can be collided with)
 * Returns true for all block types except air
 */
bool isBlockSolid(BlockType type)
{
    return type != BLOCK_AIR;
}

/**
 * Get the rectangle coordinates for a block at the given grid position
 * Converts grid coordinates to world coordinates
 */
Rectangle getBlockRect(int x, int y)
{
    return (Rectangle){
        x * BLOCK_SIZE,
        y * BLOCK_SIZE,
        BLOCK_SIZE,
        BLOCK_SIZE
    };
}
