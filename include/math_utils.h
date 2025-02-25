#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <raylib.h>
#include <math.h>

// Fonctions mathématiques utilitaires
float clamp(float value, float min, float max);
Vector2 vector2Add(Vector2 v1, Vector2 v2);
Vector2 vector2Scale(Vector2 v, float scale);
float vector2Length(Vector2 v);

#endif // MATH_UTILS_H
