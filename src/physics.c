#include "../include/physics.h"
#include "../include/world.h"

bool checkCollision(Rectangle a, Rectangle b)
{
    return CheckCollisionRecs(a, b);
}

/**
 * Check for collisions between player hitbox and world blocks
 * Returns true if a collision was detected and fills the correction vector
 */
bool checkWorldCollision(Rectangle hitbox, struct World *world, Vector2 *correction)
{
    bool collided = false;
    *correction = (Vector2){0, 0};

    // Étendre la zone de recherche pour être sûr de ne pas manquer de blocs
    int startX = (int)((hitbox.x - 5) / BLOCK_SIZE);
    int startY = (int)((hitbox.y - 5) / BLOCK_SIZE);
    int endX = (int)((hitbox.x + hitbox.width + 5) / BLOCK_SIZE);
    int endY = (int)((hitbox.y + hitbox.height + 5) / BLOCK_SIZE);

    // Limiter aux dimensions du monde
    startX = fmax(0, startX);
    startY = fmax(0, startY);
    endX = fmin(WORLD_WIDTH - 1, endX);
    endY = fmin(WORLD_HEIGHT - 1, endY);

    // Vérifier d'abord les collisions verticales (priorité au sol)
    for (int x = startX; x <= endX; x++)
    {
        for (int y = startY; y <= endY; y++)
        {
            if (isBlockSolid(world->blocks[x][y]))
            {
                Rectangle blockRect = getBlockRect(x, y);

                if (CheckCollisionRecs(hitbox, blockRect))
                {
                    collided = true;

                    // Calculer la pénétration dans toutes les directions
                    float leftPen = (blockRect.x + blockRect.width) - hitbox.x;
                    float rightPen = (hitbox.x + hitbox.width) - blockRect.x;
                    float topPen = (blockRect.y + blockRect.height) - hitbox.y;
                    float bottomPen = (hitbox.y + hitbox.height) - blockRect.y;

                    // Trouver la pénétration la plus faible (correction minimale)
                    float minPen = leftPen;
                    Vector2 minCorr = (Vector2){ leftPen, 0 };

                    if (rightPen < minPen) {
                        minPen = rightPen;
                        minCorr = (Vector2){ -rightPen, 0 };
                    }

                    if (topPen < minPen) {
                        minPen = topPen;
                        minCorr = (Vector2){ 0, topPen };
                    }

                    if (bottomPen < minPen) {
                        minPen = bottomPen;
                        minCorr = (Vector2){ 0, -bottomPen };
                    }

                    // Prioriser les corrections verticales (pour le saut/gravité)
                    if (fabs(minCorr.y) > 0) {
                        correction->y = minCorr.y;
                        return true;  // Retourner immédiatement pour une collision verticale
                    }
                    else {
                        correction->x = minCorr.x;  // Stocker la correction horizontale pour plus tard
                    }
                }
            }
        }
    }

    return collided;
}
