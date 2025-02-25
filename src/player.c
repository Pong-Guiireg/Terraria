#include "../include/player.h"
#include "../include/world.h"

#define PLAYER_SPEED 5.0f
#define JUMP_FORCE 10.0f
#define GRAVITY 0.5f

/**
 * Initialize the player entity
 * Places the player at the center of the world horizontally
 * and at a safe height above the terrain
 */
void initPlayer(Player *player)
{
    float centerX = (WORLD_WIDTH / 2) * BLOCK_SIZE;
    float centerY = 10 * BLOCK_SIZE;

    player->position = (Vector2){ centerX, centerY };
    player->velocity = (Vector2){ 0, 0 };

    // Légèrement réduire la hitbox pour éviter les accrochages
    player->hitbox = (Rectangle){
        player->position.x + 2,  // Décaler un peu pour centrer
        player->position.y,
        BLOCK_SIZE - 6,  // Plus étroite
        BLOCK_SIZE * 2 - 4  // Hauteur inchangée
    };

    player->isJumping = false;
    player->isFalling = true;
}

/**
 * Update the player's state for one frame
 * Handles gravity, movement, and world collisions
 */
void updatePlayer(Player *player, World *world)
{
    applyGravity(player);

    // Séparer le mouvement horizontal et vertical pour mieux gérer les collisions
    // D'abord mouvement horizontal
    float oldVelocityY = player->velocity.y;  // Utiliser float au lieu de Vector2
    player->velocity.y = 0;
    updatePlayerPosition(player);
    checkWorldCollisions(player, world);

    // Ensuite mouvement vertical
    player->velocity.y = oldVelocityY;  // Réassigner la valeur float
    player->velocity.x = 0;
    updatePlayerPosition(player);
    checkWorldCollisions(player, world);

    // Une dernière vérification pour être sûr
    Vector2 correction = {0, 0};
    if (checkWorldCollision(player->hitbox, world, &correction)) {
        player->position.x += correction.x;
        player->position.y += correction.y;
        player->hitbox.x = player->position.x;
        player->hitbox.y = player->position.y;
    }
}

/**
 * Render the player on screen
 * Draws the player hitbox as a red rectangle
 */
void renderPlayer(Player *player)
{
    DrawRectangleRec(player->hitbox, RED);
}

/**
 * Set the player's velocity to move left
 */
void movePlayerLeft(Player *player)
{
    player->velocity.x = -PLAYER_SPEED;
}

/**
 * Set the player's velocity to move right
 */
void movePlayerRight(Player *player)
{
    player->velocity.x = PLAYER_SPEED;
}

/**
 * Make the player jump if they are on the ground
 * Only allows jumping when not already jumping or falling
 */
void playerJump(Player *player)
{
    if (!player->isFalling)
    {
        player->velocity.y = -JUMP_FORCE;
        player->isJumping = true;
    }
}

/**
 * Apply gravity and horizontal friction to the player
 * Limits the maximum falling speed
 */
void applyGravity(Player *player)
{
    player->velocity.y += GRAVITY;
    player->velocity.x *= 0.8f;

    if (player->velocity.y > 15.0f)
        player->velocity.y = 15.0f;
}

/**
 * Update the player's position based on their velocity
 * Also updates the hitbox position
 */
void updatePlayerPosition(Player *player)
{
    float step_y = player->velocity.y;

    if (fabsf(step_y) > BLOCK_SIZE/4.0f) {
        int steps = ceilf(fabsf(step_y) / (BLOCK_SIZE/4.0f));
        step_y = player->velocity.y / steps;

        for (int i = 0; i < steps; i++) {
            player->position.y += step_y;
            player->hitbox.y = player->position.y;
        }
    } else {
        player->position.y += player->velocity.y;
    }

    float step_x = player->velocity.x;
    if (fabsf(step_x) > BLOCK_SIZE/4.0f) {
        int steps = ceilf(fabsf(step_x) / (BLOCK_SIZE/4.0f));
        step_x = player->velocity.x / steps;

        for (int i = 0; i < steps; i++) {
            player->position.x += step_x;
            player->hitbox.x = player->position.x;
        }
    } else {
        player->position.x += player->velocity.x;
    }

    player->hitbox.x = player->position.x;
    player->hitbox.y = player->position.y;
}

/**
 * Check and resolve collisions between the player and the world
 * Updates player state (jumping/falling) based on collisions
 */
void checkWorldCollisions(Player *player, World *world)
{
    Vector2 correction = { 0, 0 };

    if (checkWorldCollision(player->hitbox, world, &correction))
    {
        // Appliquer une correction plus forte pour éviter que le joueur ne reste coincé
        player->position.x += correction.x * 1.1f;  // 10% de plus
        player->position.y += correction.y * 1.1f;  // 10% de plus

        player->hitbox.x = player->position.x;
        player->hitbox.y = player->position.y;

        // Arrêter complètement le mouvement dans la direction de la collision
        if (correction.y < 0)
        {
            player->velocity.y = 0;
            player->isJumping = false;
            player->isFalling = false;
        }
        else if (correction.y > 0)
        {
            player->velocity.y = 0;
            player->isJumping = false;
            player->isFalling = true;
        }

        if (correction.x != 0)
        {
            player->velocity.x = 0;
        }

        // Vérification supplémentaire pour s'assurer qu'on est bien sorti du bloc
        Vector2 extraCorrection = {0, 0};
        if (checkWorldCollision(player->hitbox, world, &extraCorrection)) {
            player->position.x += extraCorrection.x * 1.5f;  // Correction plus forte
            player->position.y += extraCorrection.y * 1.5f;  // Correction plus forte
            player->hitbox.x = player->position.x;
            player->hitbox.y = player->position.y;
        }
    }
    else
    {
        // En l'air
        if (player->velocity.y > 0) {
            player->isFalling = true;
            player->isJumping = false;
        } else if (player->velocity.y < 0) {
            player->isJumping = true;
        }
    }

    // Toujours synchroniser la hitbox avec la position
    player->hitbox.x = player->position.x;
    player->hitbox.y = player->position.y;
}
