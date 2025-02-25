#include "../include/utils.h"
#include "../include/player.h"
#include "../include/world.h"
#include "../include/render.h"
#include "../include/global.h"

// Variables globales
extern Player player_instance;
extern World world_instance;

/**
 * Initialize the game environment
 * Creates the window and initializes all game subsystems
 */
void init_game(void)
{
    InitWindow(1280, 720, "Terraria Remake");
    SetTargetFPS(60);

    // Utiliser les noms corrects des fonctions
    initPlayer(&player_instance);
    initWorld(&world_instance);
    init_render();
}

/**
 * Update the game state for one frame
 * Handles player physics and world interactions
 */
void update_game(void)
{
    // Utiliser les noms corrects des fonctions
    updatePlayer(&player_instance, &world_instance);
    update_world();
}

/**
 * Update the world state for one frame
 * Currently empty but reserved for future world dynamics
 */
void update_world(void)
{
    // Placeholder for world update logic
}

/**
 * Clean up all resources when the game exits
 * Closes the rendering window and frees memory
 */
void cleanup_game(void)
{
    CloseWindow();
}
