#include "../include/render.h"

// Variable globale pour la caméra
Vector2 camera_offset = {0, 0};

// Référence au joueur - déclaration externe seulement
// Suppression de la définition ici car elle est déjà dans global.c
extern Player player_instance;
extern World world_instance;

/**
 * Initialize the rendering system
 * Sets the initial camera position
 */
void init_render(void)
{
    // Initialiser la caméra à (0,0)
    camera_offset = (Vector2){0, 0};
}

/**
 * Render a complete frame of the game
 * Clears the screen and draws all game elements
 */
void render_game(void)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    update_camera();
    render_world();
    render_player();

    EndDrawing();
}

/**
 * Update the camera position to follow the player
 * Centers the view on the player and applies world boundaries
 */
void update_camera(void)
{
    // Récupérer les dimensions de la hitbox du joueur pour l'utiliser comme width/height
    float player_width = player_instance.hitbox.width;
    float player_height = player_instance.hitbox.height;

    // Faire suivre la caméra au joueur (centrer)
    camera_offset.x = player_instance.position.x - SCREEN_WIDTH / 2 + player_width / 2;
    camera_offset.y = player_instance.position.y - SCREEN_HEIGHT / 2 + player_height / 2;

    // Empêcher la caméra de sortir des limites du monde
    camera_offset.x = clamp(camera_offset.x, 0, WORLD_WIDTH * BLOCK_SIZE - SCREEN_WIDTH);
    camera_offset.y = clamp(camera_offset.y, 0, WORLD_HEIGHT * BLOCK_SIZE - SCREEN_HEIGHT);
}

/**
 * Render the visible portion of the world
 * Only draws blocks that are currently visible on screen
 */
void render_world(void)
{
    // Calculer les limites visibles du monde (optimisé pour un monde plus grand)
    int start_x = (int)(camera_offset.x / BLOCK_SIZE);
    int start_y = (int)(camera_offset.y / BLOCK_SIZE);
    int end_x = start_x + (SCREEN_WIDTH / BLOCK_SIZE) + 2;  // +2 pour éviter les artefacts visuels aux bords
    int end_y = start_y + (SCREEN_HEIGHT / BLOCK_SIZE) + 2;

    // Limiter les indices pour éviter de déborder du tableau
    start_x = clamp(start_x, 0, WORLD_WIDTH - 1);
    start_y = clamp(start_y, 0, WORLD_HEIGHT - 1);
    end_x = clamp(end_x, 0, WORLD_WIDTH);
    end_y = clamp(end_y, 0, WORLD_HEIGHT);

    // Dessiner les blocs visibles
    for (int x = start_x; x < end_x; x++) {
        for (int y = start_y; y < end_y; y++) {
            BlockType block = world_instance.blocks[x][y];

            if (block != BLOCK_AIR) {
                float draw_x = x * BLOCK_SIZE - camera_offset.x;
                float draw_y = y * BLOCK_SIZE - camera_offset.y;

                DrawRectangle(
                    draw_x, draw_y,
                    BLOCK_SIZE, BLOCK_SIZE,
                    get_block_color(block)
                );
            }
        }
    }
}

/**
 * Render the player character
 * Draws the player at the correct position relative to the camera
 */
void render_player(void)
{
    // Dessiner le joueur exactement à sa position de hitbox
    // Cela permet de visualiser si la hitbox est correctement positionnée
    DrawRectangle(
        player_instance.hitbox.x - camera_offset.x,
        player_instance.hitbox.y - camera_offset.y,
        player_instance.hitbox.width,
        player_instance.hitbox.height,
        RED
    );
}

/**
 * Get the appropriate color for a block type
 * Maps each block type to its visual representation
 */
Color get_block_color(BlockType block)
{
    switch (block) {
        case BLOCK_GRASS: return GREEN;
        case BLOCK_DIRT: return BROWN;
        case BLOCK_STONE: return GRAY;
        default: return WHITE;
    }
}
