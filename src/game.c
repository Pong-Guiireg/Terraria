#include "../include/game.h"

// Variables globales à partager avec render.c
extern Player player_instance;
extern World world_instance;

/**
 * Initialize the game state
 * Sets up the window, game entities, and rendering
 */
void initGame(Game *game)
{
    InitWindow(1280, 720, "Terraria");
    SetTargetFPS(60);

    game->running = true;
    initPlayer(&game->player);
    initWorld(&game->world);

    // Initialiser les variables globales pour le rendu
    player_instance = game->player;
    world_instance = game->world;

    // Initialiser le rendu
    init_render();
}

/**
 * Run the main game loop
 * Handles input, updates game state, and renders each frame
 */
void runGameLoop(Game *game)
{
    while (!WindowShouldClose() && game->running)
    {
        handleInput(game);
        updateGame(game);

        // Mettre à jour les variables globales pour le rendu
        player_instance = game->player;

        // Appeler render_game au lieu de renderGame
        render_game();
    }
}

/**
 * Clean up resources when the game ends
 */
void cleanupGame(Game *game)
{
    (void)game;  // Indique que nous savons que le paramètre n'est pas utilisé
    CloseWindow();
}

/**
 * Update the game state for one frame
 */
void updateGame(Game *game)
{
    updatePlayer(&game->player, &game->world);
}

/**
 * Handle player input
 * Processes keyboard commands for player movement and game control
 */
void handleInput(Game *game)
{
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        movePlayerLeft(&game->player);

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        movePlayerRight(&game->player);

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
        playerJump(&game->player);

    if (IsKeyPressed(KEY_ESCAPE))
        game->running = false;
}
