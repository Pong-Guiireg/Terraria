#ifndef RENDER_H
#define RENDER_H

#include "math_utils.h"
#include "world.h"
#include "player.h"

// Constantes d'écran
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// Déclaration des fonctions de rendu
void init_render(void);
void render_game(void);
void update_camera(void);
void render_world(void);
void render_player(void);
Color get_block_color(BlockType block);

// Variables externes
extern Vector2 camera_offset;
extern Player player_instance;

#endif // RENDER_H
