#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>
#include <stdbool.h>
#include <math.h>

// Fonctions mathématiques utilitaires
float clamp(float value, float min, float max);
Vector2 vector2Add(Vector2 v1, Vector2 v2);
Vector2 vector2Scale(Vector2 v, float scale);
float vector2Length(Vector2 v);

// Déclarations externes des fonctions de gestion globale du jeu
// Ces fonctions seront définies dans game_utils.c
extern void init_game(void);
extern void update_game(void);
extern void update_world(void);
extern void cleanup_game(void);

#endif // UTILS_H
